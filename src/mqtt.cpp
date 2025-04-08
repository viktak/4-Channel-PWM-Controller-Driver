#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#include "TimeChangeRules.h"
#include "mqtt.h"
#include "common.h"
#include "version.h"
#include "settings.h"
#include "main.h"
#include "mosfet.h"

#define MQTT_BUFFER_SIZE 1024 * 5

WiFiClient client;
PubSubClient PSclient(client);

unsigned long heartbeatMillis = 0;

void ConnectToMQTTBroker()
{
    if (!PSclient.connected())
    {
        SerialMon.printf("Connecting to MQTT broker %s... ", appSettings.mqttServer);

        char msg[100];
        sprintf(msg, "{\"System\":{\"Hostname\":\"%s\",\"Status\":\"offline\"}}", appSettings.hostName);

        char myTopic[MAX_MQTT_TOPIC_LENGTH];
        sprintf(myTopic, "%s/%s", appSettings.mqttTopic, MQTT_STATE_TOPIC);

        if (PSclient.connect(appSettings.hostName, appSettings.mqttUserName, appSettings.mqttPassword, myTopic, 0, true, msg))
        {
            SerialMon.println(" Success.");

            //  Send state
            sprintf(myTopic, "%s/%s", appSettings.mqttTopic, MQTT_STATE_TOPIC);
            sprintf(msg, "{\"System\":{\"Hostname\":\"%s\",\"Status\":\"online\"}}", appSettings.hostName);
            PSclient.publish(myTopic, msg, true);

            //  Send heartbeat
            SendHeartbeat();

            //  Listening to commands
            sprintf(myTopic, "%s/%s/#", appSettings.mqttTopic, MQTT_COMMAND_TOPIC);
            PSclient.subscribe(myTopic, 0);
        }
        else
        {
            SerialMon.println(" failed. Check broker settings, credentials, access.");
        }
    }
}

void SendDataToBroker(const char *topic, const char data[], bool retained)
{
    if (strlen(appSettings.mqttServer) == 0)
        return;

    if (PSclient.connected())
    {
        PSclient.publish(topic, data, retained);
    }
}

void SendChannelTelemetry(const size_t channel, const uint8_t value)
{
    if (strlen(appSettings.mqttServer) == 0)
        return;

    // SerialMon.printf("Channel: %i\tValue: %i\r\n", channel, value);

    //  Prepare value
    char myValue[4];
    sprintf(myValue, "%i", value);

    //  Prepare topic
    char myTopic[MAX_MQTT_TOPIC_LENGTH];
    sprintf(myTopic, "%s/%s/%i", appSettings.mqttTopic, MQTT_TELEMETRY_TOPIC, channel, myValue);

    //  Send data
    SendDataToBroker(myTopic, myValue, appSettings.mqttRetain);
}

void SendHeartbeat()
{
    char buffer[MQTT_BUFFER_SIZE];
    JsonDocument doc;

    JsonObject sysDetails = doc["System"].to<JsonObject>();

    sysDetails["ChipID"] = GetChipID();
    TimeChangeRule *tcr;
    time_t localTime = timechangerules::timezones[appSettings.timeZone]->toLocal(now(), &tcr);
    sysDetails["Time"] = DateTimeToString(localTime);
    sysDetails["FriendlyName"] = appSettings.friendlyName;
    sysDetails["Freeheap"] = ESP.getFreeHeap();

    sysDetails["HardwareID"] = HARDWARE_ID;
    sysDetails["HardwareVersion"] = HARDWARE_VERSION;
    sysDetails["FirmwareID"] = FIRMWARE_ID;
    sysDetails["FirmwareVersion"] = FIRMWARE_VERSION;
    sysDetails["UpTime"] = TimeIntervalToString(millis() / 1000);
    sysDetails["CPU0_ResetReason"] = GetResetReasonString(rtc_get_reset_reason(0));
    sysDetails["CPU1_ResetReason"] = GetResetReasonString(rtc_get_reset_reason(1));
    sysDetails["TIMEZONE"] = appSettings.timeZone;

    JsonObject mqttDetails = doc["MQTT"].to<JsonObject>();

    mqttDetails["MQTT_SERVER"] = appSettings.mqttServer;
    mqttDetails["MQTT_PORT"] = appSettings.mqttPort;
    mqttDetails["MQTT_TOPIC"] = appSettings.mqttTopic;

    JsonObject wifiDetails = doc["WiFi"].to<JsonObject>();
    wifiDetails["SSID"] = appSettings.ssid;
    wifiDetails["Channel"] = WiFi.channel();
    wifiDetails["HostName"] = appSettings.hostName;
    wifiDetails["IP_Address"] = WiFi.localIP().toString();
    wifiDetails["MAC_Address"] = WiFi.macAddress();

    serializeJson(doc, buffer);

    char myTopic[MAX_MQTT_TOPIC_LENGTH];
    sprintf(myTopic, "%s/%s", appSettings.mqttTopic, MQTT_HEARTBEAT_TOPIC);
    SendDataToBroker(myTopic, buffer, false);
}

void mqttCallback(char *topic, byte *payload, unsigned int len)
{

    char msg[len + 1];
    memcpy(msg, payload, len);
    msg[len] = '\0';

#ifdef __debugSettings
    SerialMon.printf("Message received in [%s]:\r\n", topic);
    SerialMon.println(msg);
    SerialMon.println();
#endif

    //  Determine channel
    const char *lastSlash = strrchr(topic, '/');
    const char *strChannel = lastSlash ? lastSlash + 1 : topic;

    SetLEDGamma(atoi(strChannel), atoi(msg));
}

void setupMQTT()
{
    if (strlen(appSettings.mqttServer) == 0)
        return;
    PSclient.setServer(appSettings.mqttServer, appSettings.mqttPort);
    PSclient.setKeepAlive(MQTT_KEEP_ALIVE_PERIOD);
    PSclient.setCallback(mqttCallback);
    if (!PSclient.setBufferSize(MQTT_BUFFER_SIZE))
    {
        SerialMon.printf("Could not resize MQTT buffer to %u.\r\n", MQTT_BUFFER_SIZE);
    }
    heartbeatMillis = millis();
}

void loopMQTT()
{
    if (strlen(appSettings.mqttServer) == 0)
        return;

    if (PSclient.connected())
    {
        PSclient.loop();
        if (millis() - heartbeatMillis > appSettings.heartbeatInterval * 1000)
        {
            SendHeartbeat();
            heartbeatMillis = millis();
        }
    }
    else
    {
        ConnectToMQTTBroker();
    }
}
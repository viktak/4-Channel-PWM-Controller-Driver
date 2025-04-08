#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <Preferences.h>
#include <nvs_flash.h>

#define SerialMon Serial

#define ESP_ACCESS_POINT_NAME_SIZE 63

////////////////////////////////////////////////////////////////////

enum OPERATION_MODES
{
    WIFI_SETUP,
    NORMAL
};

////////////////////////////////////////////////////////////////////

const int32_t DEBUG_SPEED = 115200;
const String HARDWARE_ID = "4 Channel PWM Controller/Driver";
const String HARDWARE_VERSION = "1.0";
const String FIRMWARE_ID = "LED PWM";

class settings
{
public:
    //  System
    u_char FailedBootAttempts;

    char adminPassword[32];

    char ssid[32];
    char password[32];

    char AccessPointSSID[32];
    char AccessPointPassword[32];

    char hostName[24];

    char friendlyName[32];

    signed char timeZone;

    u_int heartbeatInterval;

    const char *GetOperationModeString();

    //  Wifi

    //  MQTT
    char mqttServer[64];
    uint16_t mqttPort;
    char mqttTopic[64];
    char mqttUserName[64];
    char mqttPassword[64];
    bool mqttRetain;

    //  Operation
    OPERATION_MODES opMode;
    bool flipButtons;


    //  functions
    void SetupFileSystem();
    void Load(bool LoadDefaults = false);
    void Save();

    void ClearNVS();

    String GetDeviceMAC();
    void PrintSettings();

    settings();
};

#endif
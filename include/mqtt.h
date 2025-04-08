#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>

#include "main.h"

#define MQTT_KEEP_ALIVE_PERIOD 60 //  seconds

#define MAX_MQTT_TOPIC_LENGTH 192

#define MQTT_STATE_TOPIC "state"
#define MQTT_COMMAND_TOPIC "cmnd"
#define MQTT_HEARTBEAT_TOPIC "heartbeat"
#define MQTT_TELEMETRY_TOPIC "tele"

void SendChannelTelemetry(const size_t channel, const uint8_t value);

void SendHeartbeat();

void setupMQTT();
void loopMQTT();

#endif
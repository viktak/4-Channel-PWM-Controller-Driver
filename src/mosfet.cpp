#include <Arduino.h>

#include "mosfet.h"
#include "mqtt.h"

unsigned long mosfetMillis = 0;

uint8_t LEDGamma[NUMBER_OF_CHANNELS];
uint8_t currentLEDValue[NUMBER_OF_CHANNELS];

void MaxLEDGamma(size_t channel)
{
    LEDGamma[channel] = sizeof(LEDGamma_lut) / sizeof(uint8_t) - 1;
    SendChannelTelemetry(channel, LEDGamma[channel]);
}

void MinLEDGamma(size_t channel)
{
    LEDGamma[channel] = 0;
    SendChannelTelemetry(channel, LEDGamma[channel]);
}

void IncreaseLEDGamma(size_t channel)
{
    if (LEDGamma[channel] < sizeof(LEDGamma_lut) / sizeof(uint8_t) - 1)
        LEDGamma[channel]++;
    SendChannelTelemetry(channel, LEDGamma[channel]);
}

void DecreaseLEDGamma(size_t channel)
{
    if (LEDGamma[channel] > 0)
        LEDGamma[channel]--;
    SendChannelTelemetry(channel, LEDGamma[channel]);
}

void SetLEDGamma(size_t channel, uint8_t value)
{
    SerialMon.printf("Setting channel #%i to %i\r\n", channel, value);
    LEDGamma[channel] = value;
    SendChannelTelemetry(channel, LEDGamma[channel]);
}

void setupMOSFET()
{
    ledcSetup(0, LEDC_FREQ, LEDC_RESOLUTION);
    ledcAttachPin(MOSFET0_GPIO, 0);
    ledcWrite(0, 0);

    ledcSetup(1, LEDC_FREQ, LEDC_RESOLUTION);
    ledcAttachPin(MOSFET1_GPIO, 1);
    ledcWrite(1, 0);

    ledcSetup(2, LEDC_FREQ, LEDC_RESOLUTION);
    ledcAttachPin(MOSFET2_GPIO, 2);
    ledcWrite(2, 0);

    ledcSetup(3, LEDC_FREQ, LEDC_RESOLUTION);
    ledcAttachPin(MOSFET3_GPIO, 3);
    ledcWrite(3, 0);

    for (size_t i = 0; i < NUMBER_OF_CHANNELS; i++)
    {
        LEDGamma[i] = 0;
        currentLEDValue[i] = 0;
    }
}

void loopMOSFET()
{
    if (millis() > mosfetMillis + 20)
    {
        for (size_t i = 0; i < NUMBER_OF_CHANNELS; i++)
        {
            if (LEDGamma_lut[LEDGamma[i]] - currentLEDValue[i] > 0)
                currentLEDValue[i]++;

            if (LEDGamma_lut[LEDGamma[i]] - currentLEDValue[i] < 0)
                currentLEDValue[i]--;

            ledcWrite(i, currentLEDValue[i]);
        }

        mosfetMillis = millis();
    }
}

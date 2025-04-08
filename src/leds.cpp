#include <Esp.h>
#include "leds.h"

void connectionLED_TOGGLE()
{
    digitalWrite(CONNECTION_STATUS_LED_GPIO, 1 - digitalRead(CONNECTION_STATUS_LED_GPIO));
}

void connectionLED_ON()
{
    digitalWrite(CONNECTION_STATUS_LED_GPIO, LOW);
}

void connectionLED_OFF()
{
    digitalWrite(CONNECTION_STATUS_LED_GPIO, HIGH);
}

void loopLEDs()
{
}

void setupLEDs()
{
    pinMode(CONNECTION_STATUS_LED_GPIO, OUTPUT);
    digitalWrite(CONNECTION_STATUS_LED_GPIO, HIGH);
}

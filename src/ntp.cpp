#include <WiFi.h>
#include <WiFiUdp.h>
#include <TimeLib.h>

#include <NTPClient.h>

#include "ntp.h"
#include "common.h"

WiFiUDP ntpUDP;

char timeServer[] = "europe.pool.ntp.org";

NTPClient timeClient(ntpUDP, timeServer, 0, NTP_UPDATE_INTERVAL_MS);

void setupNTP()
{
    timeClient.begin();
}

void loopNTP()
{
    timeClient.update();
    if (timeClient.isTimeSet())
    {
        setTime(timeClient.getEpochTime());
    }
}

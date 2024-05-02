#ifndef CUSTOMTIME_H
#define CUSTOMTIME_H

#include <Arduino.h>

#include <TimeLib.h>

#include "constants.h"

class CustomTime{
    public:
        CustomTime(
          int gmtOffset, 
          int daylightOffset, 
          const char* ntpServer, 
          int timeSyncInterval
        );
        
        bool begin();

        long unixFromTimestamp(String timestamp);
        String timestampFromUnix(long unix);

        long getUnixTime();
        String getTimestamp();

        int getHour();
        int getMinute();

        void setGmtOffset(int gmtOffset);
        void setDaylightOffset(int daylightOffset);

        void setTime(long time);
        void setNtpServer(const char* ntpServer);
        void setTimeSyncInterval(int timeSyncInterval);

    private:
        bool _getTime();

        int _gmt_offset;
        int _daylight_offset;
        const char* _ntp_server;
        int _time_sync_interval;
};

#endif
#include "customtime.h"

CustomTime::CustomTime(
    int gmtOffset, 
    int daylightOffset,
    const char* ntpServer,
    int timeSyncInterval) {
        _gmt_offset = gmtOffset;
        _daylight_offset = daylightOffset;
        _ntp_server = ntpServer;
        _time_sync_interval = timeSyncInterval;
}

bool CustomTime::begin(){
    configTime(_gmt_offset, _daylight_offset, _ntp_server);
    setSyncInterval(_time_sync_interval);
    if (_getTime()){
        Serial.printf("Time synchronized: %s\n", getTimestamp().c_str());
        return true;
    } else {
        Serial.println("Failed to synchronize time");
        return false;
    }
}

bool CustomTime::_getTime() {
    time_t _now;
    struct tm _timeinfo;
    if(!getLocalTime(&_timeinfo)){ 
        return false;
    }
    time(&_now);
    return true;
}

long CustomTime::unixFromTimestamp(String timestamp){
    struct tm _timeinfo;
    strptime(timestamp.c_str(), TIMESTAMP_FORMAT, &_timeinfo);
    return mktime(&_timeinfo);
}

String CustomTime::timestampFromUnix(long unix){
    struct tm* _timeinfo;
    char _timestamp[26];

    _timeinfo = localtime(&unix);
    strftime(_timestamp, sizeof(_timestamp), TIMESTAMP_FORMAT, _timeinfo);
    return String(_timestamp);
}

long CustomTime::getUnixTime(){
    return static_cast<long>(time(nullptr));
}

String CustomTime::getTimestamp(){
    return timestampFromUnix(getUnixTime());
}

int CustomTime::getHour(){
    struct tm _timeinfo;
    if(!getLocalTime(&_timeinfo)){ 
        return -1;
    }
    return _timeinfo.tm_hour;
}

int CustomTime::getMinute(){
    struct tm _timeinfo;
    if(!getLocalTime(&_timeinfo)){ 
        return -1;
    }
    return _timeinfo.tm_min;
}

void CustomTime::setGmtOffset(int gmtOffset){
    _gmt_offset = gmtOffset;
    begin();
}

void CustomTime::setDaylightOffset(int daylightOffset){
    _daylight_offset = daylightOffset;
    begin();
}

void CustomTime::setNtpServer(const char* ntpServer){
    _ntp_server = ntpServer;
    begin();
}

void CustomTime::setTimeSyncInterval(int timeSyncInterval){
    _time_sync_interval = timeSyncInterval;
    begin();
}

void CustomTime::setTime(long unix){
    struct timeval _tv;
    _tv.tv_sec = unix;
    settimeofday(&_tv, nullptr);
}

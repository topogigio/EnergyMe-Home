#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

#include <SPIFFS.h>
#include <ArduinoJson.h>

#include "constants.h"
#include "customtime.h"
#include "led.h"

extern CustomTime customTime;
extern Led led;

class Logger{
  public:
    Logger();

    void begin();

    void log(const char* message, const char* function, int logLevel);
    void logOnly(const char* message, const char* function, int logLevel);
    void setPrintLevel(int printLevel);
    void setSaveLevel(int saveLevel);

    String getPrintLevel();
    String getSaveLevel();

    void setDefaultLogLevels();
    bool setLogLevelsFromSpiffs();

    int getNumberOfLinesInLogFile();
    void keepLastXLines(int numberOfLinesToKeep);
    void clearLog();
    
  private:
    void _save(const char* messageFormatted);
    void _saveLogLevelsToSpiffs();

    int _print_level;
    int _save_level;

    String _logLevelToString(int logLevel);
    int _saturateLogLevel(int logLevel);
};

#endif
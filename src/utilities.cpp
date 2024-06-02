#include "utilities.h"
#include <iostream>
#include <cstdlib>
#include <map>


static LogLevel currentLogLevel = getEnvironmentLogLevel();

LogLevel getEnvironmentLogLevel() {
    const char* env_val = std::getenv("LOG_LEVEL");
    if (!env_val) return LogLevel::LevelNone;  // Default to NONE if unset

    std::string logLevel(env_val);

    if (logLevel == "NONE") return LogLevel::LevelNone;
    if (logLevel == "DEBUG") return LogLevel::LevelDebug;
    if (logLevel == "INFO") return LogLevel::LevelInfo;
    if (logLevel == "ERROR") return LogLevel::LevelError;

    return LogLevel::LevelNone;  // Default if unmatched
}


bool isLogLevel(LogLevel level) {
    return currentLogLevel != LogLevel::LevelNone && level >= currentLogLevel;
}


void log(const std::string& message, LogLevel level) {
    if (isLogLevel(level)) {
        if (level == LogLevel::LevelError) {
            std::cerr << message << std::endl;
        } else {
            std::cout << message << std::endl;
        }
    }
}


LogLevel checkLogLevel() {
    return currentLogLevel;
}


void echoLogLevel() {
    currentLogLevel = getEnvironmentLogLevel();
    std::string logLevelStr;
    switch (currentLogLevel) {
        case LogLevel::LevelNone: logLevelStr = "NONE"; break;
        case LogLevel::LevelDebug: logLevelStr = "DEBUG"; break;
        case LogLevel::LevelInfo: logLevelStr = "INFO"; break;
        case LogLevel::LevelError: logLevelStr = "ERROR"; break;
        default: logLevelStr = "UNKNOWN"; break;
    }
    std::cout << "Current log level: " << logLevelStr << std::endl;
}

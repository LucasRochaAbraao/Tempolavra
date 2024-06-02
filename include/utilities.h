#pragma once

#include <string>

extern unsigned int leds_bitmask[];

const int LED_MATRIX_WIDTH = 15;
const int LED_MATRIX_HEIGHT = 15;

enum class LogLevel {
    LevelNone,
    LevelDebug,
    LevelInfo,
    LevelError
};

void echoLogLevel();
LogLevel getEnvironmentLogLevel();
bool isLogLevel(LogLevel level);
void log(const std::string& message, LogLevel level);

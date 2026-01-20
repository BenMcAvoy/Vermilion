#pragma once

#include <ntddk.h>

#define LOG_LEVEL_NONE  0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARN  2
#define LOG_LEVEL_INFO  3
#define LOG_LEVEL_DEBUG 4

// FINDME: Log level
#define LOG_LEVEL LOG_LEVEL_DEBUG

#define LOG_PRINT(levelStr, fmt, ...) \
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "[Vermilion][%s] %s:%d: " fmt "\n", \
        levelStr, __FUNCTION__, __LINE__, __VA_ARGS__)

#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERROR(fmt, ...) LOG_PRINT("ERROR", fmt, __VA_ARGS__)
#else
#define LOG_ERROR(fmt, ...) (void)0
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN
#define LOG_WARN(fmt, ...) LOG_PRINT("WARN", fmt, __VA_ARGS__)
#else
#define LOG_WARN(fmt, ...) (void)0
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(fmt, ...) LOG_PRINT("INFO", fmt, __VA_ARGS__)
#else
#define LOG_INFO(fmt, ...) (void)0
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOG_DEBUG(fmt, ...) LOG_PRINT("DEBUG", fmt, __VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...) (void)0
#endif


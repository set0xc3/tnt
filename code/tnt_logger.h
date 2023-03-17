#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <string.h>

void log_info(const char* tag, const char* fmt, ...);

#define LOG_INFO(...)    log_info("[INFO] ", ##__VA_ARGS__)
#define LOG_DEBUG(...)   log_info("[DEBUG] ", ##__VA_ARGS__)
#define LOG_WARNING(...) log_info("[WARNING] ", ##__VA_ARGS__)
#define LOG_ERROR(...)   log_info("[ERROR] ", ##__VA_ARGS__)
#define LOG_FATAL(...)   log_info("[FATAL] ", ##__VA_ARGS__)

#endif //LOGGER_H

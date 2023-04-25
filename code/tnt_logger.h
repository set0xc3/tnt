#ifndef LOGGER_H
#define LOGGER_H

#include "tnt_types.h"

#include <stdio.h>
#include <string.h>

internal void log_info(const char *tag, const char *fmt, ...)
{
	local_variable char log_buffer[1024];
	sprintf(log_buffer, "%s", tag);
	va_list va;
	va_start(va, fmt);
	local_variable char buffer[1024];
	vsprintf(buffer, fmt, va);
	strncat(log_buffer, buffer, 1024);
	fprintf(stderr, "%s\n", log_buffer);
	va_end(va);
}

#define LOG_INFO(...) log_info("[INFO]    ", ##__VA_ARGS__)
#define LOG_DEBUG(...) log_info("[DEBUG]   ", ##__VA_ARGS__)
#define LOG_WARNING(...) log_info("[WARNIG]  ", ##__VA_ARGS__)
#define LOG_ERROR(...) log_info("[ERROR]   ", ##__VA_ARGS__)
#define LOG_FATAL(...) log_info("[FATAL]   ", ##__VA_ARGS__)

#endif // LOGGER_H

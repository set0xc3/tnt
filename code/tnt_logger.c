#include "tnt_logger.h"

void log_info(const char* tag, const char* fmt, ...) {
	char log_buffer[512];
	sprintf(log_buffer, "%s", tag);
	va_list va;
	va_start(va, fmt);
	char buffer[512];
	vsprintf(buffer, fmt, va);
	strncat(log_buffer, buffer, 512);
	fprintf(stderr, "%s\n", log_buffer);
	va_end(va);
}

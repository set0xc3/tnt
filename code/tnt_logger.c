
internal void log_info(const char* tag, const char* fmt, ...)
{
	char log_buffer[512];
	sprintf(log_buffer, "%s", tag);
	va_list va;
	va_start(va, fmt);
	char buffer[512];
	vsprintf(buffer, fmt, va);
	strcat(log_buffer, buffer);
	fprintf(stderr, "%s\n", log_buffer);
	va_end(va);
}
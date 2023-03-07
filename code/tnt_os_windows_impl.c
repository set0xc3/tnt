#include <windows.h>
#include <shellapi.h>

TNT_API void* os_memory_reserve(void* start, const u64 size) {
	local_variable void* result;
	result = VirtualAlloc(start, size, MEM_COMMIT, PAGE_READWRITE);
	if (result) {
		return result;
	} else {
		LOG_ERROR("Failed reserve memory");
		ASSERT(true);
		return 0;
	}
	
    return result;
}

TNT_API void os_memory_release(void* memory, const u64 size) {
	local_variable i32 is_error;
	is_error = VirtualFree(memory, 0, MEM_RELEASE);
	if (!is_error) {
		LOG_ERROR("Failed release memory");
		ASSERT(true);
	}
}

TNT_API u64 os_page_size(void) {
	local_variable LPSYSTEM_INFO info;
	GetSystemInfo(&info);
	return (u64)info.dwPageSize;
}

TNT_API void os_sleep(const u32 milliseconds) {
	Sleep(milliseconds);
}

TNT_API void* os_library_load(const char* path) {
	local_variable HMODULE result;
	
	char path_ext[512] = {0};
	strcpy(path_ext, path);
	strncat(path_ext, PLATFORM_LIBRARY_EXTENSION, strlen(path_ext));
	
	result = LoadLibraryA(path_ext);
	if (result) {
		return result;
	} else if (result == (HMODULE)0) {
		LOG_ERROR("Failed load library");
		ASSERT(true);
		return 0;
	}
}

TNT_API void* os_library_load_symbol(void* library_handle, const char* name) {
	local_variable FARPROC result;
	result = GetProcAddress(library_handle, name);
	if (result) {
		return result;
	}
	else {
		LOG_ERROR("Failed load library symbol");
		ASSERT(true);
		return 0;
	}
}

TNT_API void os_library_unload(void* library_handle) {
	local_variable BOOL result;
	result = FreeLibrary(handle);
	if (!result) {
		LOG_ERROR("Failed unload library symbol");
		ASSERT(true);
	}
}

TNT_API u64 os_time_now(void) {
	local_variable LARGE_INTEGER result;
	QueryPerformanceCounter(&result);
	return result.QuadPart;
}

TNT_API u64 os_time_frequency(void) {
	local_variable LARGE_INTEGER result;
	QueryPerformanceFrequency(&result);
	return result.QuadPart;
}
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <dlfcn.h>

internal void* os_memory_alloc(void* start, const u64 size) {
    void* result = mmap(start, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (result != MAP_FAILED) {
		return result;
	} else {
		LOG_ERROR("Failed reserve memory");
		ASSERT(true);
		return 0;
	}
}

internal void os_memory_free(void* memory, const u64 size) {
	if (memory) {
		i32 error = munmap(memory, size);
		if (error == -1) {
			LOG_ERROR("Failed release memory");
			ASSERT(true);
		}
	} else {
		LOG_ERROR("Failed release memory");
		ASSERT(true);
	}
}

internal u64 os_page_size(void) {
	i64 size = sysconf(_SC_PAGESIZE);
	if (size == -1) {
		LOG_ERROR("Failed get page size memory");
		ASSERT(true);
	}
    return size;
}

internal void os_sleep(const u32 milliseconds) {
	usleep(milliseconds);
}

internal void* os_library_load(const char* library_path) {
	void* result = 0;
	
	u64 len    = strlen(library_path);
	char* path = malloc(len);
	strncpy(path, library_path, len);
	strncat(path, PLATFORM_LIBRARY_EXTENSION, strlen(PLATFORM_LIBRARY_EXTENSION));
	
    result = dlopen(path, RTLD_LAZY); 
	if (result) {
		return result;
	} else {
		LOG_ERROR("Failed load library");
		ASSERT(true);
		return 0;
	}

	free(path);
}

internal void* os_library_load_symbol(void* library_handle, const char* name) {
	void* result = dlsym(library_handle, name); 
	if (result) {
		return result;
	} else {
		LOG_ERROR("Failed load library symbol");
		ASSERT(true);
		return 0;
	}
    return result;
}

internal void os_library_unload(void* library_handle) {
	i32 is_error = dlclose(library_handle); 
	if (is_error != 0) {
		LOG_ERROR("Failed unload library");
		ASSERT(true);
	}
}
#include "tnt_logger.h"
#include "tnt_os.h"
#include "tnt_types_platform.h"
#include "tnt_string.h"

#include <dlfcn.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void *os_memory_alloc(void *start, const u64 size) {
  void *result = mmap(start, size, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (result != MAP_FAILED) {
    return result;
  } else {
    LOG_ERROR("Failed reserve memory");
    ASSERT(true);
    return 0;
  }
}

void os_memory_free(void *memory, const u64 size) {
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

u64 os_page_size(void) {
  i64 size = sysconf(_SC_PAGESIZE);
  if (size == -1) {
    LOG_ERROR("Failed get page size memory");
    ASSERT(true);
  }
  return size;
}

// void os_sleep(u32 milliseconds) { 
// 	usleep(milliseconds); 
// }

void *os_library_load(String8 path) {
  void *result = 0;

	u64 size = str_len(path) + strlen(PLATFORM_LIBRARY_EXTENSION);
	String8 new_path = {(u8*)alloca(size), size};
	strncpy(str8_to_char(new_path), str8_to_char(path), str_len(new_path));
	strncat(str8_to_char(new_path), PLATFORM_LIBRARY_EXTENSION, sizeof(new_path));

  result = dlopen(str8_to_char(new_path), RTLD_NOW);
  if (result) {
    return result;
  } else {
    LOG_ERROR("Failed load library");
    ASSERT(true);
    return 0;
  }
}

void *os_library_load_symbol(void *library_handle, String8 name) {
  void *result = dlsym(library_handle, str8_to_char(name));
  if (result) {
    return result;
  } else {
    LOG_ERROR("Failed load library symbol");
    ASSERT(true);
    return 0;
  }
  return result;
}

void os_library_unload(void *library_handle) {
  i32 is_error = dlclose(library_handle);
  if (is_error != 0) {
    LOG_ERROR("Failed unload library");
    ASSERT(true);
  }
}

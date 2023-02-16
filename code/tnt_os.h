#ifndef OS_H
#define OS_H

typedef struct OS_State OS_State;
struct OS_State
{
	
};

internal void  os_init(void);
internal void  os_shutdown(void);

internal void *os_memory_alloc(void *start, const u64 size);
internal void  os_memory_free(void *memory, const u64 size);

internal u64   os_page_size(void);

internal void  os_sleep(const u32 milliseconds);

internal u64   os_time_now(void);
internal u64   os_time_frequency(void);

internal void *os_library_load(const char *path);
internal void *os_library_load_symbol(void* library_handle, const char *name);
internal void  os_library_unload(void* library_handle);

#endif //OS_H
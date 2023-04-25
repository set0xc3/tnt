#if !defined(TNT_THREAD_H)
#define TNT_THREAD_H

#include "tnt_types.h"

u64 os_thread_create(Function func);
void os_thread_run();

#endif // TNT_THREAD_H

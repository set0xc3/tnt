#if !defined(TNT_THREAD_H)
#define TNT_THREAD_H

#include "tnt_base_types.h"

u64 os_thread_create(FunctionHandle *func);
void os_thread_run(void);

#endif  // TNT_THREAD_H

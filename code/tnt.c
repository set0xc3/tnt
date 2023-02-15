#include "tnt.h"
#include "tnt_linked_list.c"
#include "tnt_logger.c"

#ifdef PLATFORM_LINUX
#include "tnt_os_linux_impl.c"
#include "tnt_os_linux_entry.c"
#elif PLATFORM_WINDOWS
#include "tnt_os_windows_impl.c"
#include "tnt_os_windows_entry.c"
#endif

#include "tnt_os_window.c"
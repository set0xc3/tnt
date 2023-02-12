#include "tnt.h"
#include "tnt_linked_list.c"
#include "tnt_logger.c"

#ifdef PLATFORM_LINUX
#include "tnt_os_linux_impl.c"
#elif PLATFORM_WINDOWS
#include "tnt_os_windows_impl.c"
#endif

#include "tnt_os_main.c"
#ifdef PLATFORM_LINUX
#include "tnt_os_linux_main.c"
#elif PLATFORM_WINDOWS
#include "tnt_os_windows_main.c"
#endif

#include "tnt_os_window.c"
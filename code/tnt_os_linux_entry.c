#include "tnt_application.h"
#include "tnt_net.h"
#include "tnt_logger.h"
#include "tnt_thread.h"
#include "tnt_os.h"

b32 is_server = false;

int main(int argc, char *argv[])
{
#if 1
	if (argc > 1)
	{
		for (i32 i = 0; i < argc; i += 1)
		{
			char *arg = argv[i];
			if (!strcmp(arg, "server"))
			{
				is_server = true;
			}
		}
	}

	net_init();
	if (!is_server)
	{
		if (net_server_connect("127.0.0.1", 3490))
		{
			while (true)
			{
				net_handler();
				os_sleep(100);
			}
		}
	}
	else
	{
		if (net_server_run("127.0.0.1", 3490))
		{
			while (true)
			{
				net_handler();
				net_server_broadcast();
				os_sleep(100);
			}
		}
	}

#endif

	// application_init();
	// application_run();

	LOG_DEBUG("[OS] shutdown...");

	return 0;
}

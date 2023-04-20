#include "tnt_application.h"
#include "tnt_net.h"
#include "tnt_logger.h"
#include "tnt_thread.h"

b32 is_server = false;

int main(int argc, char *argv[]) 
{
#if 1
	if (argc > 1) {
		for (i32 i = 0; i < argc; i += 1) {
			char *arg = argv[i];
			if (!strcmp(arg, "server")) {
				is_server = true;
			}
		}
	}

	net_init();
	if (!is_server) {
		if (net_client_connect("127.0.0.1", 3490)) {
			// while (true) {
			// 	net_client_handler();
			// }
		}
	} else {
			if (net_server_run("127.0.0.1", 3490)) {
				net_server_listen();
			}
	}


#endif

	// application_init();
	// application_run();
	
	LOG_DEBUG("[OS] shutdown...");

	return 0;
}

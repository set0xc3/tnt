// #include "tnt_application.h"
#include "tnt_net.h"
#include "tnt_logger.h"

b32 is_server = false;

int main(int argc, char *argv[]) 
{
	if (argc > 1) {
		for (i32 i = 0; i < argc; i += 1) {
			char *arg = argv[i];
			if (!strcmp(arg, "server")) {
				is_server = true;
			}
		}
	}

	if (!is_server) {
		if (net_client_connect("127.0.0.1", 3490)) {
			LOG_DEBUG("[APP] Net: client connected");
			while (true) {
			}
		}
	} else {
			if (net_server_run("127.0.0.1", 3490)) {
				LOG_DEBUG("[APP] Net: server running");
				net_server_listen();
			}
	}


	// application_init();
	// application_run();
	
	return 0;
}

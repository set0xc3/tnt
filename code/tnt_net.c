#include "tnt_net.h"
#include "tnt_logger.h"
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_ERROR -1 
#define SERVER_LISTENS_MAX 256
#define SERVER_CLIENTS_MAX 256

struct NET_Connection {
	char              *ip;
	u32                port;
	i32                socket;
	struct sockaddr_in socket_addr;
};

global_variable NET_Connection client, server = {0};
global_variable NET_Connection clients[SERVER_CLIENTS_MAX];
global_variable u64            clients_count = 0;

b32 net_client_connect(char *ip, u32 port)
{
	i32 is_error = -1;

	client.ip     = ip;
	client.port   = port;
	client.socket = socket(AF_INET, SOCK_STREAM, 0);

	// create socket
	if (client.socket == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	// setting socket
	client.socket_addr.sin_family      = AF_INET;
	client.socket_addr.sin_addr.s_addr = inet_addr(client.ip);
	client.socket_addr.sin_port        = htons(client.port);

	if (client.socket == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	// connect to remote server
	is_error = connect(client.socket, (struct sockaddr *)&client.socket_addr, sizeof(client.socket_addr));
	if (is_error == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed connect server");
		return false;
	}

	return true;
}

b32 net_server_disconnect()
{
	return false;
}

b32 net_server_run(char *ip, u32 port)
{
	i32 is_error = -1;

	server.ip     = ip;
	server.port   = port;
	server.socket = socket(AF_INET, SOCK_STREAM, 0);

	// create socket
	if (server.socket == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	// setting socket
	server.socket_addr.sin_family      = AF_INET;
	server.socket_addr.sin_addr.s_addr = inet_addr(server.ip);
	server.socket_addr.sin_port        = htons(server.port);

	if (server.socket == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	is_error = bind(server.socket, (struct sockaddr *)&server.socket_addr, sizeof(server.socket_addr));
	if (is_error == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed bind");
		return false;
	}

	is_error = listen(server.socket, SERVER_LISTENS_MAX);
	if (is_error == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed listern");
		return false;
	}

	return true;
}

b32 net_server_listen()
{
	NET_Connection *client = 0;
	i32 client_socket_len = sizeof(struct sockaddr_in);
	while (true) {
		client = net_connection_get(clients_count);
		client->socket = accept(server.socket, (struct sockaddr *)&server.socket_addr, (socklen_t *)&client_socket_len);
		if (client->socket != SERVER_ERROR) {
			// NOTE(duck): get ip from new client
			getsockname(client->socket, (struct sockaddr*)&client->socket_addr, (socklen_t *)&client_socket_len);

			client->ip = inet_ntoa(client->socket_addr.sin_addr);
			client->port = ntohs(client->socket_addr.sin_port);
			client->socket = client->socket;
			net_connection_push(client);	
			LOG_DEBUG("[NET] Client connected(%i): %s:%u", client->socket, client->ip, client->port);
		} else {
			LOG_ERROR("[NET] Failed accept");
			return false;
		}
	}

	return true;
}

b32 net_server_handler()
{
	return 0;
}

void net_connection_push(NET_Connection *client)
{
	// TODO(duck): assert
	
	clients[clients_count] = *client;
	clients_count += 1;
}

NET_Connection *net_connection_get(u32 index)
{
	// TODO(duck): assert
	
	return &clients[index];
}

NET_Connection *net_connection_pop()
{
	// TODO(duck): assert
	
	memset(&clients[clients_count], 0, sizeof(NET_Connection));
	clients_count -= 1;
	NET_Connection *result = &clients[clients_count];
	return result;
}


#include "tnt_net.h"
#include "tnt_logger.h"
#include "tnt_os.h"
#include "tnt_thread.h"

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>

#define SERVER_ERROR -1 
#define SERVER_SUCCESS 0 
#define SERVER_LISTENS_MAX 2
#define SERVER_CONNECTIONS_MAX 2

typedef struct NET_Connection NET_Connection;
struct NET_Connection {
	char              *ip;
	u32                port;
	i32                socket;
	struct sockaddr_in socket_addr;
};

global_variable u8  *connections;
global_variable u64  connections_count = 0;

global_variable NET_Connection *g_server = 0;
global_variable NET_Connection *g_client = 0;

void net_init()
{
	connections = (u8 *)os_memory_alloc(0, sizeof(NET_Connection) * SERVER_CONNECTIONS_MAX);
	g_client = (NET_Connection *)os_memory_alloc(0, sizeof(NET_Connection));
	g_server = (NET_Connection *)os_memory_alloc(0, sizeof(NET_Connection));
}

b32 net_client_connect(char *ip, u32 port)
{
	i32 status = -1;

	g_client->ip     = ip;
	g_client->port   = port;
	g_client->socket = socket(AF_INET, SOCK_STREAM, 0);

	// create socket
	if (g_client->socket == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	// setting socket
	g_client->socket_addr.sin_family      = AF_INET;
	g_client->socket_addr.sin_addr.s_addr = inet_addr(g_client->ip);
	g_client->socket_addr.sin_port        = htons(g_client->port);

	if (g_client->socket == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	// NOTE(duck): nonblock socket
	i32 flags = fcntl(g_client->socket, F_GETFL, 0);
	fcntl(g_client->socket, F_SETFL, flags | O_NONBLOCK);


	// connect to remote server
	status = connect(g_client->socket, (struct sockaddr *)&g_client->socket_addr, (socklen_t)sizeof(g_client->socket_addr));
	if (status == SERVER_ERROR && errno != EINPROGRESS) {
		LOG_ERROR("[NET] Failed connect server");
		close(g_client->socket);
		return false;
	}

	if (status == SERVER_ERROR && errno == EINPROGRESS) {
		struct pollfd pfd; // структура для poll
    pfd.fd = g_client->socket; // дескриптор сокета
    pfd.events = POLLOUT; // интересующее нас событие - готовность к записи

    i32 timeout = 5000; // таймаут в миллисекундах
    status = poll(&pfd, 1, timeout); // ждем готовности сокета или таймаута

    if (status == -1) { // если произошла ошибка при вызове poll
      perror("poll"); // выводим сообщение об ошибке
      close(g_client->socket); // закрываем сокет
			return false;
    } else if (status == 0) { // если наступил таймаут
      LOG_ERROR("[NET] Connection timed out"); // выводим сообщение о таймауте
      close(g_client->socket); // закрываем сокет
			return false;
    }
	}

	LOG_INFO("[NET] Server: %i:%s:%u", g_client->socket, g_client->ip, g_client->port);
	return true;
}

b32 net_client_handler()
{
	u8 buffer[4096] = {0};

	i32 ret_bytes = recv(g_client->socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
	if (ret_bytes != SERVER_ERROR) {
		LOG_INFO("[NET] Recv(%i): %s", ret_bytes, buffer);
	} else {
		LOG_ERROR("[NET] Failed recv");
	}

	ret_bytes = -1;

	return true;
}

b32 net_client_disconnect(NET_Handle client_handle)
{
	i32 status = SERVER_ERROR;
	NET_Connection *client = client_handle;

	status = close(client->socket);
	
	return status == SERVER_ERROR ? false : true;
}

b32 net_server_disconnect()
{
	return false;
}

b32 net_server_run(char *ip, u32 port)
{
	i32 status = SERVER_ERROR;

	g_server->ip     = ip;
	g_server->port   = port;
	g_server->socket = socket(AF_INET, SOCK_STREAM, 0);

	// create socket
	if (g_server->socket == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	// setting socket
	g_server->socket_addr.sin_family      = AF_INET;
	g_server->socket_addr.sin_addr.s_addr = INADDR_ANY;
	g_server->socket_addr.sin_port        = htons(g_server->port);

	if (g_server->socket == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	status = bind(g_server->socket, (struct sockaddr *)&g_server->socket_addr, sizeof(g_server->socket_addr));
	if (status == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed bind");
		close(g_server->socket);
		return false;
	}

	status = listen(g_server->socket, SERVER_LISTENS_MAX);
	if (status == SERVER_ERROR) {
		LOG_ERROR("[NET] Failed listern");
		close(g_server->socket);
		return false;
	}

	LOG_DEBUG("[NET] Server running");
	return true;
}

b32 net_server_listen()
{
	os_thread_create(net_server_handler);
	
	i32 status = SERVER_ERROR;

	LOG_INFO("[NET] Server: waiting for connetions...");

	i32 socket_len = sizeof(struct sockaddr_in);
	while (true) {
		i32 new_socket = accept(g_server->socket, (struct sockaddr *)&g_server->socket_addr, (socklen_t *)&socket_len);
		if (new_socket != SERVER_ERROR) {
			NET_Connection *client = net_connection_push();

			// NOTE(duck): get ip/port from new client
			getsockname(new_socket, (struct sockaddr*)&client->socket_addr, (socklen_t *)&socket_len);

			client->ip     = inet_ntoa(client->socket_addr.sin_addr);
			client->port   = ntohs(client->socket_addr.sin_port);
			client->socket = new_socket;

			LOG_INFO("[NET] Client connected(%i): %s:%u", client->socket, client->ip, client->port);

			char send_text[] = "[NET:SEND] Server: Hello!";
			i32 ret_bytes = net_send(client, (u8 *)send_text, sizeof(send_text));
			if (ret_bytes == SERVER_ERROR) {
					LOG_ERROR("[NET] client disconned(%i)", client->socket);
					net_client_disconnect(client);
					net_connection_pop();
			}

			LOG_DEBUG("[NET] Server:");
			LOG_DEBUG("[NET]  Clients: %u", connections_count);

		} else {
			LOG_ERROR("[NET] Failed accept");
		}
	}

	return true;
}

b32 net_server_handler()
{
	while (true) {
		for (u32 index = 0; index < connections_count; index += 1) {
			NET_Connection *conn = (NET_Connection *)connections + index;

			char send_text[] = "[NET:SEND] Server: Tick";
			i32 ret_bytes = net_send(conn, (u8 *)send_text, sizeof(send_text));
			if (ret_bytes == SERVER_ERROR) {
					LOG_ERROR("[NET] client disconned(%i)", conn->socket);
					net_client_disconnect(conn);
					net_connection_remove(conn);

					LOG_DEBUG("[NET] Server:");
					LOG_DEBUG("[NET]  Clients: %u", connections_count);
			}
		}
		os_sleep(500);
	}

	return 0;
}

NET_Handle net_connection_push()
{
	NET_Connection *conn = (NET_Connection *)connections + connections_count;

	if (connections_count < SERVER_CONNECTIONS_MAX) {
		connections_count += 1;
	} else {
		char send_text[] = "[NET:SEND] Сервер переполнен";
		i32 ret_bytes = net_send(conn, (u8 *)send_text, sizeof(send_text));
		if (ret_bytes == SERVER_ERROR) {
				net_client_disconnect(conn);
				net_connection_remove(conn);
				LOG_ERROR("[NET] Client disconned(%i)", conn->socket);
		}
	}
	return conn;
}

NET_Handle net_connection_get(u32 index)
{
	u64 offset = index * sizeof(NET_Connection);
	void *pos = connections + offset;

	return pos;
}

NET_Handle net_connection_pop()
{
	u64 offset = connections_count * sizeof(NET_Connection);
	void *pos = connections + offset;

	if (connections_count-1 > 0) {
		memset(pos, 0, sizeof(NET_Connection));

		connections_count -= 1;
		offset = connections_count * sizeof(NET_Connection);
		pos = connections + offset;

		return pos;
	}

	return pos;
}

void net_connection_remove(NET_Handle conn_handle)
{
	for (u64 index = 0; index < connections_count; index += 1) {
		NET_Connection *conn = (NET_Connection *)connections + index;

		if (conn == conn_handle) {
			memset(conn, 0, sizeof(NET_Connection));
			connections_count -= 1;
		}
	}
}

i32 net_send(NET_Handle conn_handle, u8 *buffer, u64 size)
{
	NET_Connection *conn = conn_handle;
	i32 ret_bytes = SERVER_ERROR;

	if (net_connection_is_valid(conn)) {
		ret_bytes = send(conn->socket, buffer, size, MSG_NOSIGNAL);	
		if (ret_bytes == SERVER_ERROR) {
			LOG_ERROR("[NET] Failed send package");
			return ret_bytes;
		}
	}

	return ret_bytes;
}

b32 net_connection_is_valid(NET_Handle conn_handle)
{
	NET_Connection *conn = conn_handle;
	i32 status = SERVER_ERROR;
	socklen_t len = sizeof(status);
	i32 result = getsockopt(conn->socket, SOL_SOCKET, SO_ERROR, &status, &len);

	if (result == SERVER_SUCCESS && 
			status == SERVER_SUCCESS) {
		return true;
	} else {
		LOG_ERROR("[NET] Failed getsockopt");
		return false;
	}
}

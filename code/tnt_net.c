#include "tnt_net.h"
#include "tnt_logger.h"
#include "tnt_os.h"
#include "tnt_thread.h"
#include "tnt_memory_arena.h"

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#define NET_ERROR -1
#define NET_SUCCESS 0
#define NET_LISTENS_MAX 2
#define NET_CONNECTIONS_MAX 2

typedef struct NET_Connection NET_Connection;
struct NET_Connection
{
	b32 is_valid;
	char *ip;
	u32 port;
	i32 socket;
	struct sockaddr_in socket_addr;
};

global_variable TNT_MemoryArena *arena = 0;

global_variable u8 *connections;
global_variable u64 connections_count = 0;

global_variable NET_Connection *g_server = 0;

void net_init()
{
	arena = arena_create(Gigabytes(1));

	connections = (u8 *)push_array_zero(arena, NET_Connection, NET_CONNECTIONS_MAX);
	g_server = (NET_Connection *)push_struct_zero(arena, NET_Connection);
}

b32 net_server_connect(char *ip, u32 port)
{
	i32 status = -1;

	g_server->ip = ip;
	g_server->port = port;
	g_server->socket = socket(AF_INET, SOCK_STREAM, 0);

	// create socket
	if (g_server->socket == NET_ERROR)
	{
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	// setting socket
	g_server->socket_addr.sin_family = AF_INET;
	g_server->socket_addr.sin_addr.s_addr = inet_addr(g_server->ip);
	g_server->socket_addr.sin_port = htons(g_server->port);

	if (g_server->socket == NET_ERROR)
	{
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	// NOTE(duck): nonblock socket
	i32 flags = fcntl(g_server->socket, F_GETFL, 0);
	fcntl(g_server->socket, F_SETFL, flags | O_NONBLOCK);

	if (net_server_reconnect() == NET_Result_SUCCESS)
	{
		if (net_connection_status(g_server) == NET_Result_SUCCESS)
		{
			char send_text[] = "[NET:SEND] Client: Hi!";
			i32 ret_bytes = net_send(g_server, (u8 *)send_text, sizeof(send_text));
		}
		return true;
	}

	return false;
}

b32 net_handler()
{
	i32 status = NET_ERROR;
	u8 buffer[4096] = {0};

	i32 ret_bytes = recv(g_server->socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
	if (ret_bytes > 0)
	{
		LOG_INFO("[NET] Recv(%i): %s", ret_bytes, buffer);
	}

	ret_bytes = -1;
	return true;
}

b32 net_server_run(char *ip, u32 port)
{
	i32 status = NET_ERROR;

	g_server->ip = ip;
	g_server->port = port;
	g_server->socket = socket(AF_INET, SOCK_STREAM, 0);

	// create socket
	if (g_server->socket == NET_ERROR)
	{
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	// setting socket
	g_server->socket_addr.sin_family = AF_INET;
	g_server->socket_addr.sin_addr.s_addr = INADDR_ANY;
	g_server->socket_addr.sin_port = htons(g_server->port);

	if (g_server->socket == NET_ERROR)
	{
		LOG_ERROR("[NET] Failed create socket");
		return false;
	}

	status = bind(g_server->socket, (struct sockaddr *)&g_server->socket_addr,
				  sizeof(g_server->socket_addr));
	if (status == NET_ERROR)
	{
		LOG_ERROR("[NET] Failed bind");
		close(g_server->socket);
		return false;
	}

	status = listen(g_server->socket, NET_LISTENS_MAX);
	if (status == NET_ERROR)
	{
		LOG_ERROR("[NET] Failed listern");
		close(g_server->socket);
		return false;
	}

	LOG_DEBUG("[NET] Server running");

	os_thread_create(net_server_listen);

	return true;
}

b32 net_server_listen()
{
	while (true)
	{
		i32 status = NET_ERROR;

		LOG_INFO("[NET] Server: waiting for connetions...");

		i32 socket_len = sizeof(struct sockaddr_in);
		i32 new_socket =
			accept(g_server->socket, (struct sockaddr *)&g_server->socket_addr,
				   (socklen_t *)&socket_len);
		if (new_socket != NET_ERROR)
		{
			NET_Connection *conn = (NET_Connection *)net_connection_push();

			// NOTE(duck): get ip/port from new client
			getsockname(new_socket, (struct sockaddr *)&conn->socket_addr,
						(socklen_t *)&socket_len);

			conn->ip = inet_ntoa(conn->socket_addr.sin_addr);
			conn->port = ntohs(conn->socket_addr.sin_port);
			conn->socket = new_socket;

			if (net_connection_status(conn))
			{
				LOG_INFO("[NET] Client connected(%i): %s:%u", conn->socket, conn->ip, conn->port);
				conn->is_valid = true;
			}
			else
			{
				net_connection_disconnect(conn);
				net_connection_pop();
			}
		}
		else
		{
			LOG_ERROR("[NET] Failed accept");
		}
		os_sleep(100);
	}
	return true;
}

b32 net_server_broadcast()
{
	for (u32 index = 0; index < connections_count; index += 1)
	{
		NET_Connection *conn = (NET_Connection *)connections + index;
		if (conn->is_valid)
		{
			NET_Result result = net_connection_status(conn);
			if (result == NET_Result_SUCCESS)
			{
				char send_text[] = "[NET:SEND] Server: Tick";
				i32 ret_bytes = net_send(conn, (u8 *)send_text, sizeof(send_text));
			}
			else
			{
				net_connection_disconnect(conn);
				net_connection_remove(conn);

				LOG_ERROR("[NET] client disconned(%i)\n", conn->socket);
				LOG_DEBUG("[NET] Server:");
				LOG_DEBUG("[NET]  Clients: %u", connections_count);
			}
		}
	}
	return true;
}

NET_Result net_server_reconnect()
{
	i32 status = -1;
	u32 error_count = 0;
	b32 is_connect = false;

	while (!is_connect && error_count < 2)
	{
		if (status == NET_ERROR)
		{
			status = connect(g_server->socket, (struct sockaddr *)&g_server->socket_addr,
							 (socklen_t)sizeof(g_server->socket_addr));
			NET_Result result = net_connection_status(g_server);
			switch (result)
			{
			case NET_Result_SUCCESS:
				LOG_INFO("[NET] Connect: success");
				is_connect = true;
				return result;
			case NET_Result_ERROR:
				LOG_INFO("[NET] Connect: error");
				break;
			case NET_Result_TIMEOUT:
				LOG_INFO("[NET] Connect: timeout");
				break;
			}
			error_count += 1;
		}

		os_sleep(100);
	}

	return NET_Result_ERROR;
}

NET_Handle net_connection_push()
{
	NET_Connection *conn = (NET_Connection *)connections + connections_count;

	if (connections_count < NET_CONNECTIONS_MAX)
	{
		connections_count += 1;
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

	if (connections_count - 1 > 0)
	{
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
	for (u64 index = 0; index < connections_count; index += 1)
	{
		NET_Connection *conn = (NET_Connection *)connections + index;

		if (conn == conn_handle)
		{
			memset(conn, 0, sizeof(NET_Connection));
			connections_count -= 1;
		}
	}
}

b32 net_connection_disconnect(NET_Handle conn_handle)
{
	NET_Connection *conn = conn_handle;
	i32 status = NET_ERROR;

	status = close(conn->socket);

	return status == NET_ERROR ? false : true;
}

i32 net_send(NET_Handle conn_handle, u8 *buffer, u64 size)
{
	NET_Connection *conn = conn_handle;
	i32 ret_bytes = NET_ERROR;

	ret_bytes = send(conn->socket, buffer, size, MSG_NOSIGNAL);
	if (ret_bytes == NET_ERROR)
	{
		LOG_ERROR("[NET] Failed send package");
		return ret_bytes;
	}

	return ret_bytes;
}

NET_Result net_connection_status(NET_Handle conn_handle)
{
	NET_Connection *conn = conn_handle;

	int error = 0;
	socklen_t len = sizeof(error);
	int retval = getsockopt(conn->socket, SOL_SOCKET, SO_ERROR, &error, &len);

	if (retval == NET_SUCCESS &&
		error == NET_SUCCESS)
	{
		return NET_Result_SUCCESS;
	}
	else
	{
		if (error == EPIPE)
		{
			return NET_Result_ERROR;
		}

		if (error == ECONNRESET)
		{
			return NET_Result_ERROR;
		}

		i32 timeout = 5000; // ms
		struct pollfd pfd = {0};
		pfd.fd = conn->socket;
		pfd.events = POLLIN;

		i32 retval = poll(&pfd, 1, timeout);

		if (retval > 0)
		{
			return NET_Result_SUCCESS;
		}
		else
		{
			return NET_Result_ERROR;
		}

		if (pfd.revents & POLLIN)
		{
			/* there is data to read on socket */
			char buffer[1];
			int nread = recv(conn->socket, buffer, 1, MSG_PEEK);

			if (nread > 0)
			{
				return NET_Result_SUCCESS;
			}
			else
			{
				return NET_Result_ERROR;
			}
		}
	}

	return NET_Result_ERROR;
}

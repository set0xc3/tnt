#if !defined(TNT_NET_H)

#include "tnt_types.h"

typedef u32 NET_Result;
enum {
	NET_Result_ERROR,
	NET_Result_SUCCESS,
	NET_Result_TIMEOUT,
};

typedef void* NET_Handle;

void net_init();

b32 net_handler();

b32 net_server_run(char *ip, u32 port);
b32 net_server_connect(char *ip, u32 port);
b32 net_server_listen();
b32 net_server_broadcast();
NET_Result net_server_reconnect();

NET_Handle net_connection_push();
NET_Handle net_connection_get(u32 index);
NET_Handle net_connection_pop();
void net_connection_remove(NET_Handle conn_handle);
b32 net_connection_disconnect(NET_Handle conn_handle);

i32 net_send(NET_Handle conn, u8 *buffer, u64 size);
NET_Result net_connection_status(NET_Handle conn_handle);

#endif // TNT_NET_H

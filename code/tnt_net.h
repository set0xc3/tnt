#if !defined(TNT_NET_H)

#include "tnt_types.h"

typedef void* NET_Handle;

void net_init();

b32 net_client_connect(char *ip, u32 port);
b32 net_client_handler();
b32 net_client_disconnect(NET_Handle client_handle);

b32 net_server_run(char *ip, u32 port);
b32 net_server_listen();
b32 net_server_handler();

NET_Handle net_connection_push();
NET_Handle net_connection_get(u32 index);
NET_Handle net_connection_pop();
void net_connection_remove(NET_Handle conn_handle);

i32 net_send(NET_Handle conn, u8 *buffer, u64 size);
b32 net_connection_is_valid(NET_Handle conn_handle);

#endif // TNT_NET_H

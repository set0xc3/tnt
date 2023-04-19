#if !defined(TNT_NET_H)

#include "tnt_types.h"

typedef struct NET_Connection NET_Connection;

b32 net_client_connect(char *ip, u32 port);
b32 net_client_receiver(NET_Connection *client);
b32 net_client_disconnect();

b32 net_server_run(char *ip, u32 port);
b32 net_server_listen();
b32 net_server_handler();

void net_connection_push(NET_Connection *client);
NET_Connection *net_connection_get(u32 index);
NET_Connection *net_connection_pop();

#endif // TNT_NET_H

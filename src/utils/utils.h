#pragma once

#include "../globals/types.h"

AddrFuncStruct get_addr(int port);
int start_tcp_server(const int &port, AddrFuncStruct &addr, int max_connections = 5);
int launch(int &server_socket, AddrFuncStruct &addr);

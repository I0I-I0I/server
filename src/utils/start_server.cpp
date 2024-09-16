#include <iostream>
#include <netinet/in.h>
#include "utils.h"
#include "../globals/types.h"
#include "../globals/consts.h"

int start_tcp_server(const int &port, AddrFuncStruct &addr, int max_connections) {
	int server_socket;

	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == 0) return ERROR_SOCKET;

	if (bind(server_socket, (struct sockaddr*) &addr.addr, addr.length) < 0) {
		return ERROR_BIND;
	};

	if (listen(server_socket, max_connections) < 0) {
		return ERROR_LISTEN;
	}

	std::cout << "Server started on " << port << " port" << std::endl;

	return server_socket;
}

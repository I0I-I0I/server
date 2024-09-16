#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <ostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "globals/consts.h"
#include "globals/types.h"
#include "utils/utils.h"

int main() {
	AddrFuncStruct server_addr = get_addr(PORT);

	int server_socket = start_tcp_server(PORT, server_addr);
	if (server_socket == ERROR_BIND) {
		std::cerr << "Error on bind server" << std::endl;
		return ERROR_BIND;
	} else if (server_socket == ERROR_LISTEN) {
		std::cerr << "Error on listen server" << std::endl;
		return ERROR_LISTEN;
	}

	int launch_res;
	while (true) {
		launch_res = launch(server_socket, server_addr);
		if (launch_res == ERROR_ACCEPT) {
			std::cerr << "Error on accept" << std::endl;
			return ERROR_ACCEPT;
		}
	}

	close(server_socket);
	return 0;
}

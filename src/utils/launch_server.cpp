#include "utils.h"
#include "../globals/types.h"
#include "../globals/consts.h"
#include <cstring>
#include <iostream>
#include <unistd.h>

#define BUFFER_SIZE 1024

int launch(int &server_socket, AddrFuncStruct &addr) {
	char buffer[BUFFER_SIZE] = {0};

	int new_socket = accept(server_socket, (struct sockaddr*)&addr.addr, (socklen_t*)&addr.length);
	if (new_socket < 0) return ERROR_ACCEPT;

	std::cout << "Connection accepted" << std::endl;

	const char* send_string = "hi\n";
	send(new_socket, send_string, strlen(send_string), 0);

	while(true) {
		memset(buffer, 0, BUFFER_SIZE);
		if (recv(new_socket, buffer, BUFFER_SIZE, 0) <= 0) {
			std::cerr << "Connection closed by client" << std::endl;
			break;
		}
		const char* mes_ok = "OK\n";
		send(new_socket, mes_ok, strlen(mes_ok), 0);
	}

	close(new_socket);
	return 0;
}

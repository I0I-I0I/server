#include <netinet/in.h>
#include <sys/socket.h>
#include "../globals/types.h"

AddrFuncStruct get_addr(int port) {
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	int addr_size = sizeof(server_addr);
	return {server_addr, addr_size};
}

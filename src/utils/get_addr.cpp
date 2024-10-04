#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

struct addrinfo* get_addr(const char* port) {
	struct addrinfo hints, *servinfo, *p;
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
		std::cerr << "[ERROR] getaddrinfo: " << gai_strerror(rv) << std::endl;
		exit(1);
	}

	return servinfo;
}

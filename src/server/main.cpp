#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <ostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../globals/consts.h"
#include "../utils/addr/addr.h"
#include "./server/server.h"

int main() {
	struct addrinfo *servinfo;
	int sockfd, status;

	servinfo = get_addr(PORT);
	if ((status = create_server(sockfd, servinfo, BACKLOG)) != NORMAL) {
		close(sockfd);
		return status;
	}

	std::cout << "server wait for connections..." << std::endl;

	if ((status = launch_server(sockfd)) != NORMAL) {
		close(sockfd);
		return status;
	}

	close(sockfd);

	return 0;
}

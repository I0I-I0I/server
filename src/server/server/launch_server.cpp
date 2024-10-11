#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "../../utils/addr/addr.h"
#include "../../globals/consts.h"
#include "./server.h"

int launch_server(int sockfd) {
	char s[INET_ADDRSTRLEN];
	int new_fd;
	socklen_t sin_size;
	struct sockaddr_storage their_addr;
	const int buffer_size = BUFFER_SIZE;
	const char* esc = "q";

	while (true) {
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			std::cerr << "[ERROR] accept" << std::endl;
			return ERROR_ACCEPT;
		}

		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
		std::cout << "\nserver: got connection from " << s << std::endl;

		if (fork() == 0) {
			close(sockfd);
			start_chating(new_fd, buffer_size);
			close(new_fd);
			exit(0);
		}
		close(new_fd);
	}

	return NORMAL;
}

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "utils.h"
#include "../globals/consts.h"

void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return  &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int launch_server(int sockfd) {
	char s[INET_ADDRSTRLEN];
	int new_fd;
	socklen_t sin_size;
	struct sockaddr_storage their_addr;
	const char* msg_on_con = "Hi\n";
	const int buffer_size = BUFFER_SIZE;
	char buffer[buffer_size];

	while (true) {
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			std::cerr << "[ERROR] accept" << std::endl;
			return ERROR_ACCEPT;
		}

		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
		std::cout << "server: got connection from " << s << std::endl;

		if (fork() == 0) {
			close(sockfd);
			if (send(new_fd,msg_on_con, strlen(msg_on_con), 0) == -1)
				std::cerr << "[ERROR] send" << std::endl;
			recv(new_fd, buffer, buffer_size, 0);
			std::cout << buffer;
			close(new_fd);
			std::cout << "server: connection " << s << " was closed" << std::endl;
			exit(0);
		}
		close(new_fd);
	}

	return NORMAL;
}

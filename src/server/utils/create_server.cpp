#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"
#include "../../globals/consts.h"

void sigchld_handler(int s) {
	int saved_errno = errno;
	while (waitpid(-1, NULL, WNOHANG) > 0);
	errno = saved_errno;
}

int create_server(int& sockfd, struct addrinfo* servinfo, int backlog) {
	struct addrinfo *p;
	struct sigaction sa;
	int yes = 1;

	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			std::cerr << "[ERROR] server: socket" << std::endl;
			continue;
		}
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			std::cerr << "[ERROR] setsockopt" << std::endl;
			return ERROR_SETSOCKOPT;
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			std::cerr << "[ERROR] server: bind";
			continue;
		}
		break;
	}

	if (p == NULL) {
		std::cerr << "[ERROR] on binding" << std::endl;
		return ERROR_BIND;
	}

	if (listen(sockfd, backlog) == -1) {
		std::cerr << "[ERROR] server: failed on listen" << std::endl;
		return ERROR_LISTEN;
	}

	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		std::cerr << "[ERROR] sigaction" << std::endl;
		exit(1);
	}

	return NORMAL;
}

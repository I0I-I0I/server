#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include "../../globals/consts.h"
#include "../../utils/addr/addr.h"
#include "./connection.h"

int create_connect(int &sockfd, struct addrinfo *servinfo) {
	struct addrinfo *p;
	char s[INET6_ADDRSTRLEN];

	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			std::cerr << "[ERROR] on create socket (client side)" << std::endl;
			continue;
		}
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			std::cerr << "Connect failed" << std::endl;
			close(sockfd);
			continue;
		}
		break;
	}

	if (p == NULL) {
		std::cerr << "Error on binding" << std::endl;
		return ERROR_BIND;
	}

	inet_ntop(servinfo->ai_family, get_in_addr((struct sockaddr *)servinfo->ai_addr), s, sizeof s);
	std::cout << "client: connecting to " << s << std::endl;

	freeaddrinfo(servinfo);
	return NORMAL;
}

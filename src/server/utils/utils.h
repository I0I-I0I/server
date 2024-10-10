#pragma once

#include <sys/socket.h>

struct addrinfo* get_addr(const char* port);
int create_server(int& sockfd, struct addrinfo* servinfo, int backlog);
int launch_server(int sockfd);

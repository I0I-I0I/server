#pragma once

#include <sys/socket.h>

struct addrinfo* get_addr(const char* port);
void *get_in_addr(struct sockaddr *sa);

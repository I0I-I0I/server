#pragma once

int create_server(int& sockfd, struct addrinfo* servinfo, int backlog);
int launch_server(int sockfd);
int start_chating(int& new_fd, int buffer_size);

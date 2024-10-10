#include <arpa/inet.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "utils.h"
#include "../../globals/consts.h"

struct NetworkPacketStruct {
	uint8_t length;
	char command;
	char data[BUFFER_SIZE];
};

void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return  &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int execute_cmd(char cmd[]) {
	std::string res = std::string(PATH_TO_APP) + " \"" + cmd + "\"";
	if (system(res.c_str()) != 0)
		return WRONG_COMMAND;
	return NORMAL;
}

NetworkPacketStruct get_packet(int fd, char* buffer, int buffer_size = BUFFER_SIZE) {
	NetworkPacketStruct packet;

	memset(packet.data, 0, buffer_size);
	recv(fd, buffer, buffer_size, 0);

	// packet.length = static_cast<unsigned short>(buffer[0]);
	packet.length = buffer_size;
	packet.command = buffer[0];
	for (unsigned short i = 0; i < packet.length; i++) {
		packet.data[i] += (&buffer[1])[i];
	}

	return packet;
}

int handle_command(NetworkPacketStruct packet) {
	switch (packet.command) {
		case 'q': return EXIT;
		case 'e': return execute_cmd(packet.data);
	}
	return WRONG_COMMAND;
}

int start_chating(int& new_fd, int buffer_size, const char* msg_on_con) {
	char buffer[buffer_size];
	char* msg_on_status;
	int status;
	NetworkPacketStruct packet;

	if (send(new_fd,msg_on_con, strlen(msg_on_con), 0) == -1)
		std::cerr << "[ERROR] send" << std::endl;

	while (true) {
		memset(buffer, 0, buffer_size);
		packet = get_packet(new_fd, buffer);
		status = handle_command(packet);

		if (status == EXIT) {
			msg_on_status = strdup("goodbye\n");
			send(new_fd, msg_on_status, strlen(msg_on_status), 0);
			break;
		} else if (status == WRONG_COMMAND) {
			msg_on_status = strdup("wrong command\n");
			send(new_fd, msg_on_status, strlen(msg_on_status), 0);
			continue;
		}

		if (send(new_fd, "OK\n", 3, 0) == -1)
			std::cerr << "[ERROR] send" << std::endl;
	}

	std::cout << "server: connection closed" << std::endl;

	return NORMAL;
}

int launch_server(int sockfd) {
	char s[INET_ADDRSTRLEN];
	int new_fd;
	socklen_t sin_size;
	struct sockaddr_storage their_addr;
	const int buffer_size = BUFFER_SIZE;
	const char* msg_on_con = "OK\n";
	const char* esc = "q";

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
			start_chating(new_fd, buffer_size, msg_on_con);
			close(new_fd);
			exit(0);
		}
		close(new_fd);
	}

	return NORMAL;
}

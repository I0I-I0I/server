#include <arpa/inet.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include "utils.h"
#include "../../globals/consts.h"

struct NetworkPacketStruct {
	unsigned short length;
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
	std::cout << cmd << std::endl;
	if (system(res.c_str()) != 0)
		return WRONG_COMMAND;
	return NORMAL;
}

char hex_to_char(char hex1, char hex2) {
	hex1 = std::toupper(hex1);
	hex2 = std::toupper(hex2);

	std::cout << hex1 << hex2 << " -> ";

	int value1 = (hex1 >= '0' && hex1 <= '9') ? (hex1 - '0') : (hex1 - 'A' + 10);
	int value2 = (hex2 >= '0' && hex2 <= '9') ? (hex2 - '0') : (hex2 - 'A' + 10);
	char result = static_cast<char>((value1 << 4) | value2);

	std::cout << result << std::endl;

	return result;
}

unsigned short hex_to_short(char hex1, char hex2) {
	std::string hex_string = std::string(1, hex1) + std::string(1, hex2);
	unsigned long ul = std::strtoul(hex_string.c_str(), nullptr, 16);
	return static_cast<unsigned short>(ul);
}

NetworkPacketStruct parce_packet(char* buffer, int buffer_size = BUFFER_SIZE) {
	NetworkPacketStruct packet;
	int index = 0;

	memset(packet.data, 0, buffer_size);

	packet.length = hex_to_short(buffer[0], buffer[1]);
	std::cout << "buffer -> " << buffer << std::endl;
	packet.command = hex_to_char(buffer[2], buffer[3]);
	for (unsigned short i = 0; i < (packet.length * 2) - 2; i = i + 2) {
		packet.data[index] += hex_to_char((&buffer[4])[i], (&buffer[4])[i+1]);
		index++;
	}

	std::cout << "length -> " << packet.length << std::endl;
	std::cout << "command -> " << packet.command << std::endl;
	std::cout << "data -> " << packet.data << std::endl;

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
		recv(new_fd, buffer, buffer_size, 0);
		packet = parce_packet(buffer);
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

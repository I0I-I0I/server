#include <iostream>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../utils/addr/addr.h"
#include "../globals/consts.h"
#include "../globals/types.h"
#include "../utils/packet/packet.h"
#include "../utils/transfer_data/transfer_data.h"
#include "../utils/command/command.h"
#include "./connection/connection.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "You don't pass args!" << std::endl;
		return ERROR_NO_ARGS;
	}

	int status, sockfd;
	struct addrinfo *servinfo;
	char buffer[BUFFER_SIZE];
	NetworkPacketStruct packet;

	servinfo = get_addr(PORT);
	if ((status = create_connect(sockfd, servinfo)) != NORMAL) {
		close(sockfd);
		return status;
	}
	handle_command(
		parce_packet(
			receive_data(sockfd, buffer)
		)
	);

	RequestStruct requests[] = {
		{ *argv[1], argv[2] },
		{ 'q', (char *)"" },
	};

	for (RequestStruct request : requests) {
		if (send_data(
			sockfd,
			create_packet(request.command, request.data)
		) != 0)
			std::cerr << "[ERRRO] on send data" << std::endl;
		packet = parce_packet(
			receive_data(sockfd, buffer)
		);
		handle_command(packet);
	}
	std::cout << packet.data << std::endl;

	close(sockfd);
	return NORMAL;
}

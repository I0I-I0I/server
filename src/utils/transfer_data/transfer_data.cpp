#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include "../../globals/types.h"
#include "../../utils/packet/packet.h"
#include "./transfer_data.h"

int send_data(int sockfd, NetworkPacketStruct packet) {
	const char* data = packet_to_hex(packet);
	if (send(sockfd, data, ((packet.length + BYTES_FOR_CMD + BYTES_FOR_LENGTH) * 2), 0) == -1) {
		std::cout << "[ERROR] on send data" << std::endl;
		return ERROR_SEND;
	}
	// std::cout << "Packet -> " << packet.length << " : " << packet.command << " : " << packet.data << std::endl;
	// std::cout << "Hex -> " << data << std::endl;
	return NORMAL;
}

char* receive_data(int sockfd, char* buffer) {
	memset(buffer, 0, BUFFER_SIZE);
	if (recv(sockfd, buffer, BUFFER_SIZE, 0) == -1)
		std::cout << "[ERROR] on receive data" << std::endl;
	return buffer;
}

#include <cstring>
#include <cstring>
#include <iostream>
#include "../../globals/types.h"
#include "../../globals/consts.h"
#include "../hex/hex.h"
#include "./packet.h"

NetworkPacketStruct create_packet(char command, char* data) {
	NetworkPacketStruct packet;

	packet.command = command;
	strncpy(packet.data, data, sizeof(packet.data) - 1);
	packet.length = strlen(data);

	return packet;
}

char* packet_to_hex(NetworkPacketStruct packet) {
	char* res = new char[BUFFER_SIZE];
	char data_hex[BUFFER_SIZE - (LENGTH_LEN + CMD_LEN)];
	char length_hex[LENGTH_LEN + 1];
	char command_hex[CMD_LEN + 1];
	length_hex[LENGTH_LEN] = '\0';
	command_hex[CMD_LEN] = '\0';

	short_to_hex(packet.length, length_hex);
	char_to_hex(packet.command, command_hex);
	data_to_hex(packet.data, packet.length, data_hex);

	for (int i = 0; i < LENGTH_LEN; i++)
		res[i] = length_hex[i];

	for (int i = 0; i < CMD_LEN; i++)
		res[i + LENGTH_LEN] = command_hex[i];

	for (int i = 0; i < ((packet.length + BYTES_FOR_CMD + BYTES_FOR_LENGTH) * 2); i++)
		res[i + CMD_LEN + LENGTH_LEN] = data_hex[i];

	return res;
}

NetworkPacketStruct parce_packet(char* buffer, unsigned short buffer_size) {
	if (!buffer_size)
		buffer_size = BUFFER_SIZE;

	NetworkPacketStruct packet;
	int index = 0;

	memset(packet.data, 0, buffer_size);

	// std::cout << "\nbuffer -> " << buffer << std::endl;
	packet.length = hex_to_short(buffer[0], buffer[1], buffer[2], buffer[3]);
	packet.command = hex_to_char(buffer[4], buffer[5]);
	for (unsigned short i = 0; i < packet.length * 2; i = i + 2) {
		packet.data[index] += hex_to_char((&buffer[6])[i], (&buffer[6])[i+1]);
		index++;
	}

	// std::cout << "length -> " << packet.length << std::endl;
	// std::cout << "command -> " << packet.command << std::endl;
	// std::cout << "data -> " << packet.data << std::endl;

	return packet;
}

#include <cstring>
#include <cstring>
#include <iostream>
#include "../../globals/types.h"
#include "../../globals/consts.h"
#include "../convert/convert.h"
#include "./packet.h"

NetworkPacketStruct create_packet(char command, char* data) {
	NetworkPacketStruct packet;

	packet.command = command;
	strncpy(packet.data, data, sizeof(packet.data) - 1);
	packet.length = strlen(data);

	return packet;
}

char* packet_to_chars(NetworkPacketStruct packet) {
	char length_hex[LENGTH_LEN];
	short_to_chars(packet.length, length_hex);

	char* res = new char[BUFFER_SIZE];

	for (int i = 0; i < LENGTH_LEN; i++)
		res[i] = length_hex[i];

	for (int i = 0; i < CMD_LEN; i++)
		res[i + LENGTH_LEN] = packet.command;

	for (int i = 0; i < packet.length; i++)
		res[i + CMD_LEN + LENGTH_LEN] = packet.data[i];

	return res;
}

NetworkPacketStruct parce_packet(char* buffer, unsigned short buffer_size) {
	if (!buffer_size)
		buffer_size = BUFFER_SIZE;

	NetworkPacketStruct packet;
	int index = 0;

	memset(packet.data, 0, buffer_size);

	packet.length = chars_to_short(buffer[0], buffer[1]);
	packet.command = buffer[2];
	for (unsigned short i = 0; i < packet.length; i++)
		packet.data[i] += (&buffer[3])[i];

	if (DEBUG_MODE) {
		std::cout << "length -> " << packet.length << std::endl;
		std::cout << "command -> " << packet.command << std::endl;
		std::cout << "data -> " << packet.data << std::endl;
	}

	return packet;
}

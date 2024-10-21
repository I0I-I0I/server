#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "../../globals/consts.h"
#include "../../globals/types.h"
#include "../../utils/packet/packet.h"
#include "../../utils/transfer_data/transfer_data.h"
#include "../../utils/command/command.h"
#include "./server.h"

int start_chating(int& new_fd, int buffer_size) {
	NetworkPacketStruct packet;
	AnswerStruct answer;
	const char msg_on_con[] = "200 HI";
	char* buffer = new char[BUFFER_SIZE];

	if (send_data(
		new_fd,
		create_packet('m', (char *)msg_on_con)
	) == -1)
		std::cerr << "[ERROR] send" << std::endl;

	do {
		packet = parce_packet(receive_data(new_fd, buffer));
		answer = handle_command(packet);
		if (send_data(
			new_fd,
			create_packet(answer.type, answer.msg)
		) == -1)
			std::cerr << "[ERROR] on send" << std::endl;
	}
	while (answer.type != 'q');

	std::cout << "server: connection closed\n" << std::endl;

	return NORMAL;
}

#include <cstring>
#include <iostream>
#include <string>
#include "../../globals/consts.h"
#include "../../globals/types.h"
#include "./command.h"

int execute_cmd(char cmd[]) {
	std::string res = std::string(PATH_TO_APP) + " \"" + cmd + "\"";
	if (system(res.c_str()) != 0)
		return WRONG_COMMAND;
	return NORMAL;
}

int execute_cmd_and_get_data(char* cmd, char* out_buffer) {
	std::string result = "";
	std::string command = std::string(PATH_TO_APP) + " \"" + cmd + "\"";
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);

	FILE* pipe = popen(command.c_str(), "r");
	if (!pipe) {
		std::cerr << "popen failed!" << std::endl;
		return 1;
	}

	while (fgets(buffer, BUFFER_SIZE, pipe) != nullptr)
		result += buffer;

	pclose(pipe);

	std::strcpy(out_buffer, result.c_str());
	return NORMAL;
}

AnswerStruct handle_command(NetworkPacketStruct packet) {
	char* msg = new char[BUFFER_SIZE];
	char type = 'm';
	memset(msg, 0, BUFFER_SIZE);
	switch (packet.type) {
		case 'q':
			type = 'q';
			msg = strdup("000 BYE");
			break;
		case 'm':
			msg = strdup("201 OK");
			std::cout << packet.data << std::endl;
			break;
		case 'e':
			msg = strdup("201 OK");
			if (execute_cmd(packet.data) != NORMAL)
				msg = strdup("422 Wrong command for app");
			break;
		case 'g':
			if (execute_cmd_and_get_data(packet.data, msg) != NORMAL)
				msg = strdup("501 Cannot get data from DB");
			break;
		default:
			msg = strdup("421 Wrong command");
	}
	return { type, msg };
}


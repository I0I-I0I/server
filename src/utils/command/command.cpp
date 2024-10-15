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

AnswerStruct handle_command(NetworkPacketStruct packet) {
	char* msg = new char[BUFFER_SIZE];
	memset(msg, 0, BUFFER_SIZE);
	switch (packet.command) {
		case 'q':
			msg = strdup("000 BYE");
			return { 'q', msg };
		case 'm':
			msg = strdup("201 OK");
			std::cout << packet.data << std::endl;
			return { 'm', msg };
		case 'e':
			msg = strdup("201 OK");
			if (execute_cmd(packet.data) != 0)
				msg = strdup("422 Wrong command for app");
			return { 'm', msg };
	}
	msg = strdup("421 Wrong command");
	return { WRONG_COMMAND, msg };
}

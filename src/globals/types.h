#pragma once

#include "./consts.h"
#include <cstdint>

struct NetworkPacketStruct {
	uint16_t length;
	char command;
	char data[BUFFER_SIZE];
};

struct AnswerStruct {
	char command;
	char* msg;
};

struct RequestStruct {
	char command;
	char* data;
};

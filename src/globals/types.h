#pragma once

#include "./consts.h"
#include <cstdint>

struct NetworkPacketStruct {
	uint16_t length;
	char type;
	char data[BUFFER_SIZE];
};

struct AnswerStruct {
	char type;
	char* msg;
};

struct RequestStruct {
	char type;
	char* data;
};

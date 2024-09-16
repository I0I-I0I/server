#pragma once

#include <netinet/in.h>

struct AddrFuncStruct {
	sockaddr_in addr;
	int length;
};

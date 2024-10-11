#pragma once

#include "../../globals/types.h"

int send_data(int sockfd, NetworkPacketStruct packet);
char* receive_data(int sockfd, char* buffer);

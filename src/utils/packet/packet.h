#pragma once

#include <string>
#include "../../globals/types.h"

NetworkPacketStruct create_packet(char command, char* data);

NetworkPacketStruct parce_packet(char* buffer, unsigned short buffer_size = BUFFER_SIZE);
char* packet_to_hex(NetworkPacketStruct packet);

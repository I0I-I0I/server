#pragma once

#include <string>
#include "../../globals/types.h"

char hex_to_char(char hex1, char hex2);
unsigned short hex_to_short(char hex1, char hex2, char hex3, char hex4);

void char_to_hex(char data, char* res);
void short_to_hex(uint16_t data_length, char* res);
void data_to_hex(char* data, uint8_t data_length, char* res);

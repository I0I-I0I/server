#include <cctype>
#include <cstring>
#include "./convert.h"

unsigned short chars_to_short(char char1, char char2) {
	unsigned short res = (static_cast<unsigned short>(char1) << 8) | static_cast<unsigned short>(char2);
	return res;
}

void short_to_chars(unsigned short number, char* res) {
	res[0] = (number >> 8) & 0xFF;
	res[1] = number & 0xFF;
}

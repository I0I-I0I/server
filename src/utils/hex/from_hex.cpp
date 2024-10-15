#include <cctype>
#include <cstring>
#include "./hex.h"

char hex_to_char(char hex1, char hex2) {
	hex1 = std::toupper(hex1);
	hex2 = std::toupper(hex2);

	int value1 = (hex1 >= '0' && hex1 <= '9') ? (hex1 - '0') : (hex1 - 'A' + 10);
	int value2 = (hex2 >= '0' && hex2 <= '9') ? (hex2 - '0') : (hex2 - 'A' + 10);
	char result = static_cast<char>((value1 << 4) | value2);

	return result;
}

unsigned char hex_char_to_int(char hex) {
	if (std::isdigit(hex)) {
		return hex - '0';
	} else if (std::isxdigit(hex)) {
		hex = std::tolower(hex);
		return hex - 'a' + 10;
	} else {
		return 0;
	}
}

unsigned short hex_to_short(char hex1, char hex2, char hex3, char hex4) {
	unsigned short result = 0;

	result |= hex_char_to_int(hex1) << 12;
	result |= hex_char_to_int(hex2) << 8;
	result |= hex_char_to_int(hex3) << 4;
	result |= hex_char_to_int(hex4);

	return result;
}

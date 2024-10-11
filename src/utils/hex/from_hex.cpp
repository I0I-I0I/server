#include <cstdint>
#include <cstring>
#include <iomanip>
#include <sstream>

void short_to_hex(uint16_t number, char* res) {
	std::stringstream nu;
	nu << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(number);
	std::string length = nu.str();

	if (length.size() < 4) {
		length.insert(0, 4 - length.size(), '0');
	}

	std::strcpy(res, length.c_str());
}

void data_to_hex(char* data, uint8_t data_length, char* res) {
	std::stringstream ss;

	for(int i = 0; i < data_length; i++)
		ss << std::hex << (int)data[i];

	std::string s = ss.str();
	std::strcpy(res, s.c_str());
}

void char_to_hex(char data, char* res) {
	std::stringstream ss;
	ss << std::hex << (int)data;
	std::string str = ss.str();
	std::strcpy(res, str.c_str());
}

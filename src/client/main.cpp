#include <iostream>
#include <cstring>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		std::cerr << "Could not create socket" << std::endl;
		return 1;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(64228);
	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); // Server IP

	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		std::cerr << "Connect failed" << std::endl;
		close(sock);
		return 1;
	}

	const char* data = "eprint";
	unsigned short data_length = strlen(data);

	std::stringstream ss;
	std::stringstream nu;
	for(int i = 0; i < data_length; i++)
		ss << std::hex << (int)data[i];
	nu << std::hex << data_length;

	std::string length = nu.str();
	if (length.size() == 1)
		length = "0" + length;
	std::string export_data = length + ss.str();
	std::cout << ss.str() << std::endl;
	std::cout << export_data << std::endl;

	send(sock, export_data.c_str(), sizeof export_data, 0);

	close(sock);

	return 0;
}

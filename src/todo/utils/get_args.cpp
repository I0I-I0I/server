#include <iostream>
#include <sstream>
#include <vector>
#include "utils.h"
#include "../globals/types.h"

std::vector<int> get_args(ActionStruct &action) {
	std::string prompt;
	if (action.args == "") {
		std::cout << "Choise what check ('q' for quit): ";
		getline(std::cin, prompt);
		if (prompt == "q") return {};
	}
	std::vector<int> args;
	std::istringstream iss(prompt != "" ? prompt : action.args);
	std::string arg;
	while (iss >> arg) {
		args.push_back(stoi(arg));
	}
	return args;
}


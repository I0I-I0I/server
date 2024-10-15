#include "utils.h"

ActionStruct get_action() {
	ActionStruct action;
	std::string prompt;

	std::cout << "Prompt: ";
	getline(std::cin, prompt);
	trim(prompt);

	int space = prompt.find(' ');
	if (space != -1) {
		std::string first_part = prompt.substr(0, space);
		std::string second_part = prompt.substr(space + 1);
		action.action = first_part;
		action.args = second_part;
	} else {
		action.action = prompt;
	}

	return action;
}

ActionStruct get_action(std::string str) {
	ActionStruct action;

	trim(str);
	int space = str.find(' ');
	if (space != -1) {
		std::string first_part = str.substr(0, space);
		std::string second_part = str.substr(space + 1);
		action.action = first_part;
		action.args = second_part;
	} else {
		action.action = str;
	}

	return action;
}

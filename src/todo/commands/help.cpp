#include <vector>
#include "iostream"
#include "../globals/types.h"
#include "../globals/const.h"

std::function<int()> help(std::vector<CommandsStruct> &commands, std::vector<ActionsStruct> &actions) {
	return [&commands, &actions]() {
		std::cout << "Choice what you want?\n";
		std::cout << "(help, quit)\n";
		for (CommandsStruct item : commands) {
			std::cout << "\t" << item.key << ": " << item.desc << "\n";
		}
		for (ActionsStruct item : actions) {
			std::cout << "\t" << item.key << ": " << item.desc << "\n";
		}
		std::cout << std::endl;
		return NORMAL;
	};
}

#include <functional>
#include <iostream>
#include <ostream>
#include <vector>
#include "actions/actions.h"
#include "utils/utils.h"
#include "commands/commands.h"
#include "globals/types.h"
#include "globals/const.h"
#include "db/db.h"

int main(int argc, char* argv[]) {
	std::vector<ActionsStruct> actions = {
		{ add_todo, "add", "Add todo" },
		{ remove_todo, "remove", "Remove todo" },
		{ check_todo, "check", "Check todo" },
		{ uncheck_todo, "uncheck", "Uncheck todo" },
		{ print_todo, "print", "Print all todo" },
	};
	std::vector<CommandsStruct> commands = {
		{ quit, "quit", "Quit" },
	};

	std::function<int()> help_cb = help(commands, actions);
	std::function<int(ActionStruct&)> handle_cb = handle_action(commands, actions);
	std::function<int(std::string&)> handle_prompt_cb = handle_prompt(handle_cb, help_cb);

	db_create(DB_PATH);

	std::string data;
	int res;
	if (argc > 1) {
		data = argv[1];
		res = handle_prompt_cb(data);
		if (res == WRONG_COMMAND)
			return WRONG_COMMAND;
	} else {
		std::cout << "For help (help)" << std::endl;
		while (true) {
			std::cout << "Prompt: ";
			getline(std::cin, data);
			trim(data);
			res = handle_prompt_cb(data);
			if (res == QUIT) {
				return 0;
			}
		}
	}

	return 0;
}

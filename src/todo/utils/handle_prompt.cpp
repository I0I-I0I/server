#include <functional>
#include "utils.h"
#include "../globals/types.h"
#include "../globals/const.h"

std::function<int(std::string&)> handle_prompt(
	std::function<int(ActionStruct&)>& handle_cb,
	std::function<int()>& help_cb
) {
	return [&help_cb, &handle_cb](std::string& data) {
		int sep;
		do {
			sep = data.find(';');
			std::string current = data.substr(0, sep);
			data = data.substr(sep + 1);
			trim(current);
			ActionStruct action = get_action(current);
			int flag = handle_cb(action);

			if (flag == QUIT) {
				return QUIT;
			} else if (flag == HELP) {
				help_cb();
			} else if (flag == WRONG_COMMAND) {
				std::cout << "Wrong command!" << std::endl;
				return WRONG_COMMAND;
			}
		} while (sep != -1);
		return 0;
	};
}


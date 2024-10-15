#pragma once

#include <vector>
#include "../globals/types.h"

std::function<int(ActionStruct&)> handle_action(
	std::vector<CommandsStruct> &commands,
	std::vector<ActionsStruct> &actions
);

int add_todo(ActionStruct action);
int remove_todo(ActionStruct action);
int check_todo(ActionStruct action);
int uncheck_todo(ActionStruct action);
int print_todo(ActionStruct action);

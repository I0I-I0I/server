#pragma once

#include <vector>
#include "../globals/types.h"

std::function<int()> help(std::vector<CommandsStruct> &commands, std::vector<ActionsStruct> &actions);
int quit();

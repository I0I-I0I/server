#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../globals/types.h"

void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);

void clear_input();

std::vector<int> get_args(ActionStruct &action);

ActionStruct get_action();
ActionStruct get_action(std::string str);

std::function<int(std::string&)> handle_prompt(
	std::function<int(ActionStruct&)>& handle_cb,
	std::function<int()>& help_cb
);

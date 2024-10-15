#include <string>
#include <iostream>
#include "actions.h"
#include "../db/db.h"
#include "../globals/types.h"
#include "../globals/const.h"

std::string get_todo_title() {
	std::string todo_title;
	std::cout << "Write a todo: \n\t";
	getline(std::cin, todo_title);
	std::cout << std::endl;
	return todo_title;
}

int add_todo(ActionStruct action) {
	std::string todo_title = action.args != "" ? action.args : get_todo_title();
	int rc = db_add(DB_PATH, {todo_title, "false"});
	return rc;
}

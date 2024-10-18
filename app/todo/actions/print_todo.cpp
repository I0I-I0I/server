#include <cstring>
#include <iostream>
#include <vector>
#include "actions.h"
#include "../globals/const.h"
#include "../db/db.h"
#include "./actions.h"

int print_todo(ActionStruct action) {
	std::vector<DBData> data = db_get_all(DB_PATH);
	for (int i = 0; i < data.size(); i++) {
		std::string completed = data[i].completed == false ? "false" : "true ";
		std::cout << i + 1 << ". "
			      << completed
			      << " | "
			      << data[i].title
			      << std::endl;
	}
	std::cout << std::endl;
	return NORMAL;
}

#include <vector>
#include "actions.h"
#include "../utils/utils.h"
#include "../globals/const.h"
#include "../db/db.h"

int check_todo(ActionStruct action) {
	std::vector<int> args = get_args(action);
	std::vector<DBData> data = db_get_all(DB_PATH);
	for (int& index : args) {
		db_toggle_check(DB_PATH, data, index, true);
	}
	return NORMAL;
}

int uncheck_todo(ActionStruct action) {
	std::vector<int> args = get_args(action);
	std::vector<DBData> data = db_get_all(DB_PATH);
	for (int& index : args) {
		db_toggle_check(DB_PATH, data, index, false);
	}
	return NORMAL;
}

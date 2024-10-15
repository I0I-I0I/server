#include <vector>
#include "../globals/types.h"
#include "../utils/utils.h"
#include "../globals/const.h"
#include "../db/db.h"

int remove_todo(ActionStruct action) {
	std::vector<int> args = get_args(action);
	std::vector<DBData> data = db_get_all(DB_PATH);
	for (int index : args) {
		db_remove_by_index(DB_PATH, data, index);
	}
	return NORMAL;
}

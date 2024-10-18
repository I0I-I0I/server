#include <iostream>
#include "utils.h"

void clear_input() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

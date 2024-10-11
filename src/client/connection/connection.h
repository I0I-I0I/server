#pragma once

#include <cstdint>
#include <string>
#include "../../globals/consts.h"
#include "../../globals/types.h"

int create_connect(int &sockfd, struct addrinfo *servinfo);

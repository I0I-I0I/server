#pragma once

#include <cstdint>

// Settings
constexpr const char* PORT = "64228";
constexpr const char* PATH_TO_APP = "/mnt/d/code/cpp/server/build/cli_todo";
constexpr const short BACKLOG = 5;
constexpr const uint16_t BUFFER_SIZE = 255;

const uint8_t BYTES_FOR_LENGTH = 2;
const uint8_t BYTES_FOR_CMD = 1;
const uint8_t LENGTH_LEN = BYTES_FOR_LENGTH * 2;
const uint8_t CMD_LEN = BYTES_FOR_CMD * 2;

// Returned values
constexpr const int NORMAL = 0;
constexpr const int EXIT = 1;
constexpr const int SEND_MASSAGE = 2;

constexpr const int ERROR_ACCEPT = -10;
constexpr const int ERROR_LISTEN = -11;
constexpr const int ERROR_SOCKET = -12;
constexpr const int ERROR_LAUNCH = -13;
constexpr const int ERROR_SETSOCKOPT = -14;
constexpr const int ERROR_BIND = -15;
constexpr const int ERROR_SEND = -16;
constexpr const int ERROR_RECV = -17;

constexpr const int WRONG_COMMAND = -21;
constexpr const int ERROR_NO_ARGS = -22;

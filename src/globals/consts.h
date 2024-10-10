#pragma once

// Settings
constexpr const char* PORT = "64228";
constexpr const char* PATH_TO_APP = "/mnt/d/code/cpp/Ctodo/build/cli_todo";
constexpr const short BACKLOG = 5;
constexpr const unsigned short BUFFER_SIZE = 255;

// Returned values
constexpr const int NORMAL = 0;
constexpr const int EXIT = 1;

constexpr const int ERROR_ACCEPT = -10;
constexpr const int ERROR_LISTEN = -11;
constexpr const int ERROR_SOCKET = -12;
constexpr const int ERROR_LAUNCH = -13;
constexpr const int ERROR_SETSOCKOPT = -14;
constexpr const int ERROR_BIND = -14;

constexpr const int WRONG_COMMAND = -24;

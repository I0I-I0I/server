#pragma once

constexpr const int NORMAL = 0;
constexpr const int ERROR_ACCEPT = -10;
constexpr const int ERROR_LISTEN = -11;
constexpr const int ERROR_SOCKET = -12;
constexpr const int ERROR_LAUNCH = -13;
constexpr const int ERROR_SETSOCKOPT = -14;
constexpr const int ERROR_BIND = -14;

constexpr const char* PORT = "64228";
constexpr const int BACKLOG = 5;
constexpr const int BUFFER_SIZE = 1024;

#pragma once
#include <iostream>

#define MAX_CLIENT_BUFFER_SIZE 1024

typedef void (*SERVERFP)();
typedef void (*CLIENTFP)(std::string cmd);
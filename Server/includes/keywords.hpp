#pragma once
#include <iostream>

#define MAX_CLIENT_BUFFER_SIZE 1024

static std::string INET_KEY = "lFOYz8gbu9xbhzzFyBAjUmwlorSypF";

typedef void (*SERVERFP)();
typedef void (*CLIENTFP)(std::string cmd);
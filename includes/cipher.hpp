#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>

std::string b64decode(const std::string& in);
char *unxor(char *str);
char *unxor2(char *str, char *key);
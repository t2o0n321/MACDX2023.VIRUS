#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>

std::string b64decode(const std::string& in);
std::vector<int> permute(std::vector<int>, std::vector<int>);
std::string rc4(std::vector<int> s, std::string p);

char *unxor(char *str);
char *unxor2(char *str, char *key);
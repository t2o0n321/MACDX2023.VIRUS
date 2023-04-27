#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>

std::string b64decode(const std::string& in);

char *unxor(char *str);
char *unxor2(char *str, char *key);

class xRC4
{
public:
    xRC4(std::string key);
    std::string decrypt(std::string p);
    std::string encrypt(std::string p);

private:
    std::vector<int> permute();
    std::vector<int> S;
    std::vector<int> T;
};

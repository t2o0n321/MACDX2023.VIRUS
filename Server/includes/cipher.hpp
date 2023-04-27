#include <iostream>
#include <vector>
#include <cstring>

class RC4
{
public:
    RC4(std::string key);
    std::string decrypt(std::string p);

private:
    std::vector<int> permute();
    std::vector<int> S;
    std::vector<int> T;
};

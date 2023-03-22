#include "cipher.hpp"

std::string b64decode(const std::string &in)
{
    std::string out;

    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++)
        T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    int val = 0, valb = -8;
    for (unsigned char c : in)
    {
        if (T[c] == -1)
            break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0)
        {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

char *unxor(char *str)
{
    for (long int i = 0; i < strlen(str); i++)
        str[i] = str[i] ^ char(i);
    return str;
}

char *unxor2(char *str, char *key)
{
    int sl = strlen(str);
    int kl = strlen(key);
    for (int i = 0; i < sl; i++)
    {
        int indx = i;
        if (i > (kl - 1)) indx = i % kl;
        str[i] = (str[i] - 1) ^ (key[indx]);
    }
    return str;
}
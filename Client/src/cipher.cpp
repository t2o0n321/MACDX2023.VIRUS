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
        if (i > (kl - 1))
            indx = i % kl;
        str[i] = (str[i] - 1) ^ (key[indx]);
    }
    return str;
}

xRC4::xRC4(std::string key) : S(256), T(256)
{
    // Initialize state array
    for (int i = 0; i < 256; i++)
    {
        this->S[i] = i;
        this->T[i] = key[i % key.length()];
    }
}

std::vector<int> xRC4::permute()
{
    std::vector<int> s = this->S;
    std::vector<int> t = this->T;
    int j = 0;
    int tmp;
    for (int i = 0; i < 256; i++)
    {
        j = (j + s[i] + t[i]) % 256;

        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
    return s;
}

std::string xRC4::encrypt(std::string p)
{
    std::vector<int> s = this->permute();
    int i = 0;
    int j = 0;
    int tmp = 0;
    int k = 0;

    // Temp variables
    int b;
    int c;

    int *cipher = new int[p.length()];
    std::string cipher_T;

    for (int r = 0; r < int(p.length()); r++)
    {

        i = (i + 1) % 256;
        j = (j + s[i]) % 256;

        // swap section
        b = s[i];
        s[i] = s[j];
        s[j] = b;

        tmp = (s[i] + s[j]) % 256;
        k = s[tmp];

        c = ((int)p[r] ^ k); // Cast p char as an int then xor with k

        cipher[r] = c;

        cipher_T += (char)cipher[r]; // cast int as char then append to string
    }
    return cipher_T;
}
#include "cipher.hpp"

RC4::RC4(std::string key) : S(256), T(256)
{
    // Initialize state array
    for (int i = 0; i < 256; i++)
    {
        this->S[i] = i;
        this->T[i] = key[i % key.length()];
    }
}

std::vector<int> RC4::permute()
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

std::string RC4::encrypt(std::string p)
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

        cipher_T += (char)(cipher[r] + tmp); // cast int as char and add it with the index of S-Box then append to string
    }
    return cipher_T;
}

std::string RC4::decrypt(std::string p)
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

        c = (((int)p[r] - tmp)  ^ k); // Cast p char as an int then xor with k

        cipher[r] = c;

        cipher_T += (char)cipher[r]; // cast int as char then append to string
    }
    return cipher_T;
}
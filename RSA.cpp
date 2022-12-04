#include "./RSA.h"

RSA::RSA()
{
    this->p = 3;
    this->q = 11;
    this->z = (this->p - 1) * (this->q - 1);
    this->n = this->p * this->q;

    for (this->e = 2; this->e < this->z; this->e++)
    {
        if (this->gcd(this->e, this->z) == 1)
        {
            break;
        }
    }

    for (int i = 0; i <= 9; ++i)
    {
        int x = (i * this->z) + 1;
        if (x % this->e == 0)
        {
            this->d = x / this->e;
            break;
        }
    }
}

int RSA::gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int RSA::encrypt(int m)
{
    return this->pow(m, e) % this->n;
}

int RSA::decrypt(int c)
{
    return this->pow(c, d) % this->n;
}

int RSA::pow(int x, unsigned int y)
{
    int res = 1;
    for (; y; y--)
    {
        res = (res * x) % this->n;
    }
    return res;
}

std::string RSA::encryptPassword(std::string password)
{
    std::string res = "";

    for (char c : password)
    {
        char encryptedChar = this->encrypt((int)c) + '0';
        res += encryptedChar;
    }

    return res;
}

std::string RSA::decryptPassword(std::string password)
{
    std::string res = "";

    for (char c : password)
    {
        char decryptedChar = this->decrypt((int)c) + '0';
        res += decryptedChar;
    }

    return res;
}
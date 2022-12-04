#pragma once
#ifndef _RSA_
#define _RSA_

#include <iostream>
#include <string>

// A class that defines the RSA algorithm
class RSA {
    private:
        int p, q, n, z, d = 0, e;

    public:
        RSA();
        int gcd(int a, int b);
        int encrypt(int m);
        int decrypt(int c);
        int pow(int a, unsigned int b);

        std::string encryptPassword(std::string password);
        std::string decryptPassword(std::string password);
    
};

#endif
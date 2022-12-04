#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Curse.h"

class Utilizator
{
public:
    std::string getName();
    std::string getEmail();

    Utilizator();
    Utilizator(std::string, std::string);
    std::vector<Cursa> searchTrip(Curse, std::string, std::string, std::string);
    void reserveTrip(Curse &, Cursa);

    bool isLoggedIn;

private:
    std::string name;
    std::string email;
};
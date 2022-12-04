#include <string>
#include <iostream>
#pragma once
#include <vector>
#include <stdlib.h>
#include "Curse.h"

class Operator
{
public:
    Operator();
    Operator(std::string nume);
    std::string getName();
    void addTrip(Curse &, std::string, std::string, std::string);
    void deleteTrip(Curse &, std::string, std::string, std::string);

    bool isLoggedIn;

private:
    std::string nume;
};
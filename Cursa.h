#pragma once
#include <string>
#include <vector>
#include <iostream>
class Cursa
{
public:
    Cursa(std::string, std::string, std::string, std::vector<std::string>);

    std::string getOrigin();
    std::string getDestination();
    std::string getDate();
    std::vector<std::string> getReserved();
    void setNewReservation(std::string);
    std::string toString();

private:
    std::string origine;
    std::string destinatie;
    std::string data;
    std::vector<std::string> rezervari;
};
#include "Cursa.h"

Cursa::Cursa(std::string origin, std::string destination, std::string date, std::vector<std::string> reserved_users)
{
    this->origine = origin;
    this->destinatie = destination;
    this->data = date;
    this->rezervari = reserved_users;
}

std::string Cursa::getOrigin()
{
    return this->origine;
}

std::string Cursa::getDestination()
{
    return this->destinatie;
}

std::string Cursa::getDate()
{
    return this->data;
}

std::vector<std::string> Cursa::getReserved()
{
    return this->rezervari;
}

void Cursa::setNewReservation(std::string user)
{
    this->rezervari.push_back(user);
}

std::string Cursa::toString()
{
    std::string rezervari ="";
    for(auto rezervare : this->getReserved())
    {
        rezervari += rezervare + ", ";
    }
    return "City of departure: "+ this->origine +  "\nCity of destination: " + this->destinatie + "\nDate of the trip: " +this->data + "\nUsers who have reservations: " + rezervari + "\n"; 
}
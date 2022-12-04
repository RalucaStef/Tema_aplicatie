#include "Operator.h"


Operator::Operator()
{
}

Operator::Operator(std::string name)
{
    isLoggedIn = true; // When Operator is instantiated we want this flag to be turned true. Operatorul nu poate fi instantiat daca nu esti logged in ca operator
    this->nume = name;
}

std::string Operator::getName()
{
    return this->nume;
}

void Operator::addTrip(Curse& trips, std::string origin, std::string destination, std::string date)
{
    std::vector<std::string> rezervari = {};
    Cursa newTrip = Cursa(origin,destination,date,rezervari);
    trips.addTrip(newTrip);
    std::cout<<"Added a new trip!\n\n";
}
void Operator::deleteTrip(Curse& trips, std::string origin, std::string destination, std::string date)
{

    auto trip = trips.searchTrip(origin,destination,date)[0];
    trips.deleteTrip(trip);
}

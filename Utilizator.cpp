#include "Utilizator.h"
// using namespace std;

Utilizator::Utilizator()
{
}

Utilizator::Utilizator(std::string name, std::string email)
{
    isLoggedIn = true; // When User is instantiated we want this flag to be turned true. Utilizatorul nu poate fi instantiat daca nu esti logged in ca utilizator
    this->name = name;
    this->email = email;
}

// getter
std::string Utilizator::getName()
{
    return this->name;
}

// getter
std::string Utilizator::getEmail()
{
    return this->email;
}

std::vector<Cursa> Utilizator::searchTrip(Curse trips, std::string origin, std::string destination, std::string date)
{
    return trips.searchTrip(origin, destination, date);
}

void Utilizator::reserveTrip(Curse &trips, Cursa wantedTrip)
{
    auto foundTrips = trips.searchTrip(wantedTrip.getOrigin(), wantedTrip.getDestination(), wantedTrip.getDate());
    if (foundTrips.size() == 0)
    {
        std::cout << "No trips of this format could be found: " << wantedTrip.getOrigin() << " " << wantedTrip.getDestination() << " " << wantedTrip.getDate()<<"\n\n";
    }
    else
    {
        trips.deleteTrip(foundTrips[0]);
        foundTrips[0].setNewReservation(this->getName());
        trips.addTrip(foundTrips[0]);
        std::cout << "Trip was booked!\n\n";
    }
}

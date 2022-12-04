#include "Curse.h"
// For class Curse

Curse::Curse(std::vector<std::vector<std::string>> curse)
{
    std::vector<Cursa> curseRezultat;

    for (auto cursa_stringuri : curse)
    {
        std::vector<std::string> rezervari;
        for (int i = 3; i < cursa_stringuri.size(); i++)
        {
            rezervari.push_back(cursa_stringuri[i]);
        }
        Cursa trip = Cursa(cursa_stringuri[0], cursa_stringuri[1], cursa_stringuri[2], rezervari);
        curseRezultat.push_back(trip);
    }
    this->trips = curseRezultat;
}

void Curse::addTrip(Cursa trip)
{
    this->trips.push_back(trip);
}

void Curse::deleteTrip(Cursa trip)
{
    int flag = 0;
    for (int i = 0; i < this->trips.size(); i++)
    {
        if (trip.getDestination() == this->trips[i].getDestination() &&
            trip.getOrigin() == this->trips[i].getOrigin() &&
            trip.getDate() == this->trips[i].getDate())
        {
            auto pos = this->trips.begin() + i;
            this->trips.erase(pos);
            flag = 1;
        }
    }
    if (flag == 0)
    {
        std::cout << "Trip could not be found";
    }
}

std::vector<Cursa> Curse::getTrips()
{
    return this->trips;
}

std::vector<Cursa> Curse::searchTrip(std::string origin, std::string destination, std::string date)
{
    std::vector<Cursa> result;
    for (Cursa &trip : this->trips)
    {
        bool filter = (origin == "-" ? true : (origin == trip.getOrigin())) &&
                      (destination == "-" ? true : (destination == trip.getDestination())) &&
                      (date == "-" ? true : (date == trip.getDate()));

        if (filter)
        {
            result.push_back(trip);
        }
    }
    return result;
}
std::vector<std::vector<std::string>> Curse::getRawData()
{
    std::vector<std::vector<std::string>> result;

    for (Cursa trip : this->trips)
    {
        std::vector<std::string> vec_trip;
        vec_trip.push_back(trip.getOrigin());
        vec_trip.push_back(trip.getDestination());
        vec_trip.push_back(trip.getDate());

        for (std::string rezervare : trip.getReserved())
        {
            vec_trip.push_back(rezervare);
        }

        result.push_back(vec_trip);
    }
    return result;
}

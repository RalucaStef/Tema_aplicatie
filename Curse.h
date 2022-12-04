#pragma once
#include "Cursa.h"


class Curse
{
    public:
        Curse(std::vector<std::vector<std::string>>);
        void addTrip(Cursa);
        void deleteTrip(Cursa);
        std::vector<Cursa> searchTrip(std::string,std::string,std::string);
        std::vector<Cursa> getTrips();

        std::vector<std::vector<std::string>> getRawData();

    private:
        std::vector<Cursa> trips;
};

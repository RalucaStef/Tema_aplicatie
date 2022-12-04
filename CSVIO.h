#pragma once
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

class CSVIO
{
public:
    std::vector<std::vector<std::string>> read(std::string);        // Aici va luat Fileul db_smth.csv si va returna datele sub forma de vector
    void write(std::vector<std::vector<std::string>>, std::string); // Aici va scrie la File dintr-un vector sub forma de csv
    CSVIO();

private:
    std::vector<std::string> split(std::string, char);
    int len(std::string);
};
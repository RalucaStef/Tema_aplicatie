#include "CSVIO.h"

CSVIO::CSVIO() {}

std::vector<std::vector<std::string>> CSVIO::read(std::string fileRoute)
{
    std::vector<std::vector<std::string>> resultat;
    std::string line;
    std::ifstream myfile(fileRoute);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::vector<std::string> line_separat;
            line_separat = split(line, ',');
            resultat.push_back(line_separat);
        }
        myfile.close();
    }
    else
        std::cout << "Unable to open file";

    return resultat;
};

void CSVIO::write(std::vector<std::vector<std::string>> content, std::string fileRoute)
{
    std::ofstream myfile(fileRoute);
    if (myfile.is_open())
    {
        for (auto linie : content) // linie is a vector. stringul este rezultatul appendat
        {
            std::string line = "";
            for (int i = 0; i < linie.size(); i++)
            {
                line += linie[i];
                if(i < linie.size()-1)
                {
                     line += ",";
                }   
            }
            myfile << line + "\n";
        }
        myfile.close();
    }
    else
        std::cout << "Unable to open file";
}

std::vector<std::string> CSVIO::split(std::string str, char seperator)
{
    std::vector<std::string> rezultat;
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    while (i <= len(str))
    {
        if (str[i] == seperator || i == len(str))
        {
            endIndex = i;
            std::string subStr = "";
            subStr.append(str, startIndex, endIndex - startIndex);
            rezultat.push_back(subStr);
            currIndex += 1;
            startIndex = endIndex + 1;
        }
        i++;
    }
    return rezultat;
}

int CSVIO::len(std::string str)
{
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <sstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <fstream>

using namespace std;

class User
{
private:
    string username;
    string password;

public:
    void createAccount();
    void login();
    void searchTicket();
    void bookTicket();
};

class Operator
{
public:
    bool authentication()
    {
        ifstream file;
        string username, password;

        cout << "Please enter your username: ";
        cin >> username;

        cout << "Please enter your password: ";
        cin >> password;

        if (!file.is_open())
        {
            throw runtime_error("Could not open file!");
        }

        file.open("database.csv", ios::in);

        vector<string> row;
        string line, word;

        while (!file.eof())
        {
            getline(file, line);
            stringstream s(line);

            while (getline(s, word, ','))
            {
                row.push_back(word);
            }
        }

        if (username == row[0] && password == row[1])
        {
            return true;
        }

        throw "Incorrect username or password!";

        file.close();
        return false;
    }

    void addTicket();
    void deleteTicket();
};

int main()
{
    Operator operator1;

    int x;
    // cout << "Who are you? Press the correct key according to your status:\n[1] Operator\n[2] User\n" << endl;
    cin >> x;

    if (x == 1)
    {
        cout << "Input your username and password: " << endl;
        if (operator1.authentication() == true)
        {
            cout << "Good job";
        }
    }

    return 0;
}

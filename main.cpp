#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <sstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <fstream>
#include <ctime>

using namespace std;

class RSAPass
{
private:
    int x = 11, y = 13, n, t, i, flag, len;
    long int e[50], d[50], temp[50], j;
    char en[50], m[50];

public:
    void insertPassword(char password[50])
    {
        for (i = 0; password[i] != '\0'; i++)
            m[i] = password[i];

        n = x * y;
        t = (x - 1) * (y - 1);

        len = strlen(password);
    }

    int prime(long int pr)
    {
        int i;
        j = sqrt(pr);

        for (i = 2; i <= j; i++)
            if (pr % i == 0)
                return 0;

        return 1;
    }

    long int cd(long int a)
    {
        long int k = 1;

        while (1)
        {
            k = k + t;

            if (k % a == 0)
                return (k / a);
        }
    }

    void encryption_key()
    {
        int k = 0;

        for (i = 2; i < t; i++)
        {
            if (t % i == 0)
                continue;

            flag = prime(i);

            if (flag == 1 && i != x && i != y)
            {
                e[k] = i;
                flag = cd(e[k]);

                if (flag > 0)
                {
                    d[k] = flag;
                    k++;
                }

                if (k == 99)
                    break;
            }
        }
    }

    string encrypt()
    {
        long int pt, ct, key = e[0], k;
        i = 0;

        while (i != len)
        {
            pt = m[i];
            pt = pt - 96;
            k = 1;

            for (j = 0; j < key; j++)
            {
                k = k * pt;
                k = k % n;
            }

            temp[i] = k;
            ct = k + 96;
            en[i] = ct;
            i++;
        }

        en[i] = '\0';

        string s(en);

        return s;
    }

    string decrypt()
    {
        long int pt, ct, key = d[0], k;
        i = 0;

        while (en[i] != '\0')
        {
            ct = temp[i];
            k = 1;

            for (j = 0; j < key; j++)
            {
                k = k * ct;
                k = k % n;
            }

            pt = k + 96;
            m[i] = pt;
            i++;
        }

        m[i] = '\0';

        string s(m);

        return s;
    }
};

class User : public RSAPass
{
private:
    string username;
    string password;
    string origin;
    string arrival;
    string date;
    char passwordToBeEncrypted[50];

public:
    void createAccount()
    {
        fstream file;
        file.open("databaseUser.csv", ios::app);
        cout << "Enter the username of the new account: ";
        cin >> username;

        cout << "Enter the password of the new acount: ";
        cin >> password;

        if (password.length() < 6 || password.length() > 18)
        {
            throw "The password must have in between 6 and 18 characters!";
        }

        file << username << ",";

        strcpy(passwordToBeEncrypted, password.c_str());

        insertPassword(passwordToBeEncrypted);
        encryption_key();
        string passwordEncrypted = encrypt();

        file << passwordEncrypted << "," << 0 << "\n";

        file.close();
    }
    bool login()
    {
    }
    void searchTrip()
    {
    }
    void bookTrip()
    {
    }
};

class Operator
{
private:
    string username, password, origin, arrival, date;

public:
    bool authentication()
    {
        ifstream file;
        string temp;

        cout << "Please enter your username: ";
        cin >> username;

        cout << "Please enter your password: ";
        cin >> password;

        file.open("database.csv", ios::in);

        if (!file.is_open())
        {
            throw runtime_error("Could not open file!");
        }

        vector<string> usercolumn;
        string line, user;
        int count = 0;

        // ***************
        // ***************
        // ***************
        // ******WIP******
        // ***************
        // ***************
        // ***************
        while (!file.eof())
        {
            getline(file, line);
            stringstream s(line);
            cout << line << endl;

            while (getline(s, user, ','))
            {
                usercolumn.push_back(user);
            }

            count++;
        }
        file.close();

        throw "Incorrect username or password!";

                return false;
    }

    void addTrip()
    {
        int day, month, year;

        fstream file;
        file.open("database.csv", ios::app);

        if (!file.is_open())
        {
            throw runtime_error("Could not open file!");
        }

        cout << "Please enter the city of origin: ";
        cin >> origin;

        if (!(origin[0] >= 'A' && origin[0] <= 'Z') || (origin[0] >= 'a' && origin[0] <= 'z'))
            throw "Please input the name of the city with a capital letter!";

        for (int i = 0; i < origin.length(); i++)
        {
            if (!(origin[i] >= 'a' && origin[i] <= 'z'))
            {
                throw "No city exists that contains those characters!";
            }
        }

        cout << "Please enter the city of arrival: ";
        cin >> arrival;

        if (!(arrival[0] >= 'A' && arrival[0] <= 'Z') || (arrival[0] >= 'a' && arrival[0] <= 'z'))
            throw "Please input the name of the city with a capital letter!";

        for (int i = 0; i < arrival.length(); i++)
        {
            if (!(arrival[i] >= 'a' && arrival[i] <= 'z'))
            {
                throw "No city exists that contains those characters!";
            }
        }

        cout << "Please enter the date of the trip (DD/MM/YYYY): ";
        cin >> date;

        if (date.length() != 10)
        {
            throw "The date is written incorrectly!";
        }

        if (date[2] != '/' || date[5] != '/')
        {
            throw "The date is written incorrectly!";
        }

        day = stoi(date.substr(0, 2));
        month = stoi(date.substr(3, 2));
        year = stoi(date.substr(6));

        time_t now = time(0);
        tm *ltm = localtime(&now);

        int yearNow = 1900 + ltm->tm_year;
        int monthNow = 1 + ltm->tm_mon;
        int dayNow = ltm->tm_mday;

        if (day < dayNow && month < monthNow && year < yearNow)
        {
            throw "You entered a date from the past!";
        }

        if (month < 1 && month > 12)
        {
            throw "This date does not exist!";
        }

        if (((day < 1 && day > 28) && month == 2) || ((day < 1 && day > 29) && month == 2 || (year % 4 == 0 && year % 100 != 0)) || ((day < 1 && day > 29) && month == 2 || year % 400 == 0))
        {
            throw "This date does not exist!";
        }

        if ((day < 1 && day > 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
        {
            throw "This date does not exist!";
        }

        if ((day < 1 && day > 30) && (month == 4 || month == 6 || month == 9 || month == 11))
        {
            throw "This date does not exist!";
        }

        file << username << "," << password << "," << origin << "," << arrival << "," << date << "\n";

        file.close();
    }

    void deleteTrip()
    {
        fstream file, fileTemp;
        file.open("database.csv", ios::in);
        fileTemp.open("temp.csv", ios::out);

        if (!file.is_open())
        {
            throw runtime_error("Could not open file!");
        }

        int day, month, year;

        cout << "Please enter the city of origin: ";
        cin >> origin;

        if (!(origin[0] >= 'A' && origin[0] <= 'Z') || (origin[0] >= 'a' && origin[0] <= 'z'))
            throw "Please input the name of the city with a capital letter!";

        for (int i = 0; i < origin.length(); i++)
        {
            if (!(origin[i] >= 'a' && origin[i] <= 'z'))
            {
                throw "No city exists that contains those characters!";
            }
        }

        cout << "Please enter the city of arrival: ";
        cin >> arrival;

        if (!(arrival[0] >= 'A' && arrival[0] <= 'Z') || (arrival[0] >= 'a' && arrival[0] <= 'z'))
            throw "Please input the name of the city with a capital letter!";

        for (int i = 0; i < arrival.length(); i++)
        {
            if (!(arrival[i] >= 'a' && arrival[i] <= 'z'))
            {
                throw "No city exists that contains those characters!";
            }
        }

        cout << "Please enter the date of the trip (DD/MM/YYYY): ";
        cin >> date;

        if (date.length() != 10)
        {
            throw "The date is written incorrectly!";
        }

        if (date[2] != '/' || date[5] != '/')
        {
            throw "The date is written incorrectly!";
        }

        // ***************
        // ***************
        // ***************
        // ******WIP******
        // ***************
        // ***************
        // ***************
        // function that finds the trip in the csv
        int tripNumber;

        vector<string> row;
        string word, line, temp;
        string originTemp, arrivalTemp, dateTemp;
        int count = 0, flag = 0;

        while (!file.eof() && getline(file, line))
        {
            row.clear();
            stringstream s(line);

            getline(s, originTemp, ',');
            getline(s, arrivalTemp, ',');
            getline(s, dateTemp, ',');

            if (tripNumber != count + 1)
            {
                if (!file.eof())
                {
                    fileTemp << username << "," << password << "," << origin << "," << arrival << "," << date << "\n";
                }
            }
            else
            {
                flag = 1;
            }
            if (file.eof())
            {
                break;
            }
            count++;
        }
        if (flag == 1)
        {
            cout << "The trip has been deleted!";
        }
        else
            throw "The trip number could not be found!";
        file.close();
        fileTemp.close();

        remove("database.csv");
        rename("temp.csv", "database.csv");
    }
};

int main()
{
    Operator operator1;

    int x;
    cout << "Who are you? Press the correct key according to your status:\n[1] Operator\n[2] User\n"
         << endl;
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

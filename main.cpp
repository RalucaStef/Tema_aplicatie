//  document

#include <iostream>
#include <regex>
#include <ctime>
#include "Curse.h"
#include "CSVIO.h"
#include "Utilizator.h"
#include "Operator.h"
#include "RSA.h"

#define USER_PATH "./data/db_useri.csv"
#define OPERATOR_PATH "./data/db_operatori.csv"
#define TRIP_PATH "./data/db_curse.csv"

using namespace std;

Utilizator user;
Operator op;

// Data validation section
bool validateDate(string date)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    string dayInput = date.substr(0, 2);
    string monthInput = date.substr(3, 2);
    string yearInput = date.substr(6);

    // cout<<day<<" "<<month<<" "<<year<<"\n";
    // cout<<dayInput<<" "<<monthInput<<" "<<yearInput<<"\n";

    if (stoi(yearInput) <= year)
    {
        return false;
    }
    else if (stoi(yearInput) == year && stoi(monthInput) < month)
    {
        return false;
    }
    else if (stoi(yearInput) == year && stoi(monthInput) == month && stoi(dayInput) <= day)
    {
        return false;
    }

    const regex pattern("^(?:(?:31(/|-|.)(?:0?[13578]|1[02]))\\1|(?:(?:29|30)(/|-|.)(?:0?[13-9]|1[0-2])\\2))(?:(?:1[6-9]|[2-9]\\d)?\\d{2})$|^(?:29(/|-|.)0?2\\3(?:(?:(?:1[6-9]|[2-9]\\d)?(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])00))))$|^(?:0?[1-9]|1\\d|2[0-8])(/|-|.)(?:(?:0?[1-9])|(?:1[0-2]))\\4(?:(?:1[6-9]|[2-9]\\d)?\\d{2})");
    return regex_match(date, pattern);
}

bool validateEmail(string email)
{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}

bool validateCity(string city)
{
    const regex pattern("^(\\s)*[A-Z]+((\\s)?((\'|\\-|\\.)?([A-Za-z])+))*(\\s)*$");
    return regex_match(city, pattern);
}

bool validateUsername(string username)
{
    for (int i = 0; i < username.length(); i++)
    {
        if (username[i] == ' ')
        {
            cout << "The format of the username is incorrect!\n";
            return false;
        }
    }

    CSVIO csvIO = CSVIO();
    auto useri = csvIO.read(USER_PATH);
    for (auto user : useri)
    {

        if (username == user[0])
        {
            cout << "The username already exists!\n";
            return false;
        }
    }
    return true;
}

bool validatePassword(string &password)
{
    bool lowercase = false, uppercase = false, digit = false;
    if (password.length() < 8)
    {
        cout << "The password is too short!";
        return false;
    }
    for (int i = 0; i < password.length(); i++)
    {
        if (islower(password[i]))
            lowercase = true;
        if (isupper(password[i]))
            uppercase = true;
        if (isdigit(password[i]))
            digit = true;
    }
    if (lowercase && uppercase && digit && password.length() >= 8)
    {
        return true;
    }
    return false;
}

// All login functions
bool login_user(string userName, string password)
{
    RSA rsa;
    CSVIO csvIO = CSVIO();
    auto useri = csvIO.read(USER_PATH);
    for (auto user : useri)
    {

        if (userName == user[0])
        {
            // std::string decodedPassword = rsa.decryptPassword(user[2]);
            // cout << decodedPassword;
            // cout << rsa.decryptPassword(user[2]) << endl;
            // cout << user[2] << " " << password << " " << rsa.encryptPassword(password) << " " << rsa.decryptPassword(user[2]) << "\n";
            return user[2] == rsa.encryptPassword(password); // return false if the password is not the one in the DB;
        }
    }
    return false;
}

bool login_operator(string userName, string password)
{
    CSVIO csvIO = CSVIO();
    auto operatori = csvIO.read(OPERATOR_PATH);
    for (auto op : operatori)
    {
        if (userName == op[0])
        {
            return password == op[1]; // return false if the password is not the one in the DB;
        }
    }
    return false;
}

bool create_account(string userName, string email, string password, string repeatedPassword)
{
    if (password != repeatedPassword)
    {
        throw "Password is not the repeated password!\n";
        return false;
    }

    CSVIO csvIO = CSVIO();
    auto users = csvIO.read(USER_PATH);
    RSA rsa;
    std::string encodedPassword = rsa.encryptPassword(password);
    std::vector<std::string> newUser = {userName, email, encodedPassword};
    users.push_back(newUser);
    csvIO.write(users, USER_PATH);

    return true;
}

// The "actions" of the menu
//  First action includes the login for both users and operators, as well as create an account option
bool primaActiune(int answer)
{
    switch (answer)
    {
    case 1:
    {
        string userName, email, password;

        cout << "Enter your username: ";
        cin >> userName;

        cout << "Enter your password: ";
        cin >> password;

        try
        {
            if (!login_user(userName, password))
            {
                throw "Username and password do not match!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        user = Utilizator(userName, email);
        cout << "Logged in succesfully!\n\n";
        return true;
    }
    break;
    case 2:
    {
        string userName, password;

        cout << "Enter your operator username: ";
        cin >> userName;

        cout << "Enter your password: ";
        cin >> password;

        try
        {
            if (!login_operator(userName, password))
            {
                throw "Operator username and password do not match!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        op = Operator(userName);
        cout << "Logged in succesfully!\n\n";
        return true;
    }
    break;
    case 3:
    {
        string userName, email, password, repeatedPassword;

        cout << "Enter your desired username: ";
        std::getline(std::cin >> std::ws, userName);

        try
        {
            if (!validateUsername(userName))
            {
                throw "Error!";
            }
        }
        catch (const char *msg)
        {
            cout << msg << "\n";
            return false;
        }

        cout << "Enter your email: ";
        cin >> email;

        try
        {
            if (!validateEmail(email))
            {
                throw "The email address has the wrong format!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        cout << "Enter your password: ";
        cin >> password;

        try
        {
            if (!validatePassword(password))
            {
                throw "The password does not have the expect format!\nIt must contain at least one upper character, one lower character,\na digit and it must have at least 8 characters!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        cout << "Enter your repeated password: ";
        cin >> repeatedPassword;

        try
        {
            if (!create_account(userName, email, password, repeatedPassword))
            {
                throw "Could not create a new account! Try again!\n";
            }
        }
        catch (const char msg)
        {
            cout << msg << endl;
            return false;
        }

        cout << "\nCreated account succesfully!" << endl;
        return false;
    }
    break;
    default:
        return false;
        break;
    }
}

// Second action, which includes menu navigation according to the type of account that is currently logged in
bool aDouaActiuneUser(int answer)
{
    CSVIO csvio = CSVIO();
    Curse trips = Curse(csvio.read(TRIP_PATH));
    string origin, destination, date;
    switch (answer)
    {
    case 0: // logout
        return false;
        break;
    case 1: // search trip
    {

        cout << "Enter the origin city (enter - if u want to leave this option blank): ";
        std::getline(std::cin >> std::ws, origin);

        try
        {
            if (!validateCity(origin))
            {
                throw "The city of departure has the wrong format!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        fflush(stdin);
        cout << "Enter the destination city (enter - if u want to leave this option blank): ";
        std::getline(std::cin >> std::ws, destination);

        try
        {
            if (!validateCity(destination))
            {
                throw "The city of arrival has the wrong format!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        fflush(stdin);
        cout << "Enter the date of the trip (enter - if u want to leave this option blank): ";
        std::getline(std::cin >> std::ws, date);

        try
        {
            if (!validateDate(date))
            {
                throw "The date has the wrong format or is in the past!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        auto result = user.searchTrip(trips, origin, destination, date);
        cout << "\nTrips:\n";
        for (auto r : result)
        {
            cout << r.toString();
            cout << endl;
        }
        return true;
    }
    break;
    case 2: // book trip
    {
        cout << "Enter the city of departure: ";
        std::getline(std::cin >> std::ws, origin);

        try
        {
            if (!validateCity(origin))
            {
                throw "The city of departure has the wrong format!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        fflush(stdin);
        cout << "Enter the destination city: ";
        std::getline(std::cin >> std::ws, destination);

        try
        {
            if (!validateCity(destination))
            {
                throw "The city of arrival has the wrong format!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        fflush(stdin);
        cout << "Enter the date of the trip: ";
        std::getline(std::cin >> std::ws, date);

        try
        {
            if (!validateDate(date))
            {
                throw "The date has the wrong format or is in the past!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        std::vector<std::string> rezervatii_gol = {};
        Cursa wantedTrip = Cursa(origin, destination, date, rezervatii_gol);
        user.reserveTrip(trips, wantedTrip);
        csvio.write(trips.getRawData(), TRIP_PATH);
        return true;
    }
    break;
    default:
        return false;
    }
    return false;
}

bool aDouaActiuneOp(int answer)
{
    CSVIO csvio = CSVIO();
    Curse trips = Curse(csvio.read(TRIP_PATH));
    string origin, destination, date;
    switch (answer)
    {
    case 0: // logout
        return false;
        break;
    case 1: // add trip
    {
        cout << "Enter the origin city that you want to add: ";
        std::getline(std::cin >> std::ws, origin);

        try
        {
            if (!validateCity(origin))
            {
                throw "The city of departure has the wrong format!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        fflush(stdin);
        cout << "Enter the destination city that you want to add: ";
        std::getline(std::cin >> std::ws, destination);

        try
        {
            if (!validateCity(destination))
            {
                throw "The city of arrival has the wrong format!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        fflush(stdin);
        cout << "Enter the date of the trip that you want to add: ";
        std::getline(std::cin >> std::ws, date);

        try
        {
            if (!validateDate(date))
            {
                throw "The date has the wrong format or is in the past!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        op.addTrip(trips, origin, destination, date);
        csvio.write(trips.getRawData(), TRIP_PATH);
        return true;
    }
    break;

    case 2: // delete trip
    {
        cout << "Enter the origin city that you want to delete: ";
        std::getline(std::cin >> std::ws, origin);

        try
        {
            if (!validateCity(origin))
            {
                throw "The city of departure has the wrong format!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        fflush(stdin);
        cout << "Enter the destination city that you want to delete: ";
        std::getline(std::cin >> std::ws, destination);

        try
        {
            if (!validateCity(destination))
            {
                throw "The city of arrival has the wrong format!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        fflush(stdin);
        cout << "Enter the date of the trip that you want to delete: ";
        std::getline(std::cin >> std::ws, date);

        try
        {
            if (!validateDate(date))
            {
                throw "The date has the wrong format or is in the past!\n";
            }
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            return false;
        }

        op.deleteTrip(trips, origin, destination, date);
        csvio.write(trips.getRawData(), TRIP_PATH);
        return true;
    }
    break;
    default:
        return false;
    }

    return false;
}

int main()
{
    int answer;

    while (true)
    {
        // Login input validation
        try
        {
            cout << "Welcome!\nPress 1 in order to log in as User.\nPress 2 in order to log in as Operator.\nPress 3 in order to create a new account.\n";
            cin >> answer;
        }
        catch (...)
        {
            cout << "Invalid input. Please try again!\n";
            continue;
        }

        if (primaActiune(answer))
            break; // Exit the infinite loop when the action is properly finalized without errors
        else
        {
            main();
        }
    }

    // Can only only get here if login is successful.
    int answer2;
    while (true)
    {
        cout << "Select from the following menu one of the options:\n";
        cout << "Press 0 in order to log out\n";
        if (user.isLoggedIn)
        {
            cout << "Press 1 in order to search for a trip\nPress 2 to book a trip\n";
            cin >> answer2;
            if (!aDouaActiuneUser(answer2))
            {
                main();
            }
            else
                continue;
        }
        else if (op.isLoggedIn)
        {
            cout << "Press 1 in order to add a trip\nPress 2 to delete a trip\n";
            cin >> answer2;
            if (!aDouaActiuneOp(answer2))
            {
                main();
            }
            else
                continue;
        }
    }
    return 0;
}

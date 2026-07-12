#include "../include/User.h"
#include <sstream>

using namespace std;

// Default Constructor
User::User()
{
    id = 0;
    username = "";
    email = "";
    password = "";
}

// Parameterized Constructor
User::User(int id,
           const string& username,
           const string& email,
           const string& password)
{
    this->id = id;
    this->username = username;
    this->email = email;
    this->password = password;
}

// Getters
int User::getId() const
{
    return id;
}

string User::getUsername() const
{
    return username;
}

string User::getEmail() const
{
    return email;
}

string User::getPassword() const
{
    return password;
}

// Setters
void User::setId(int id)
{
    this->id = id;
}

void User::setUsername(const string& username)
{
    this->username = username;
}

void User::setEmail(const string& email)
{
    this->email = email;
}

void User::setPassword(const string& password)
{
    this->password = password;
}

// Save User
string User::toFileString() const
{
    stringstream ss;

    ss << id << "|"
       << username << "|"
       << email << "|"
       << password;

    return ss.str();
}

// Load User
User User::fromFileString(const string& line)
{
    stringstream ss(line);

    string idStr;
    string username;
    string email;
    string password;

    getline(ss, idStr, '|');
    getline(ss, username, '|');
    getline(ss, email, '|');
    getline(ss, password);

    return User(
        stoi(idStr),
        username,
        email,
        password
    );
}
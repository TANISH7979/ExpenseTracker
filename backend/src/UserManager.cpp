#include "../include/UserManager.h"
#include <fstream>

using namespace std;

UserManager::UserManager()
{
    ifstream file("backend/data/users.txt");

    if (!file)
        return;

    string line;

    while (getline(file, line))
    {
        if (!line.empty())
        {
            users.push_back(User::fromFileString(line));
        }
    }

    file.close();
}

bool UserManager::login(const string& email,
                        const string& password)
{
    for (const auto& user : users)
    {
        if (user.getEmail() == email &&
            user.getPassword() == password)
        {
            return true;
        }
    }

    return false;
}


int UserManager::getUserId(const string& email)
{
    for (const auto& user : users)
    {
        if (user.getEmail() == email)
        {
            return user.getId();
        }
    }

    return -1;
}


bool UserManager::registerUser(const User& user)
{
    users.push_back(user);

    ofstream file("backend/data/users.txt");

    if (!file)
        return false;

    for (const auto& u : users)
    {
        file << u.toFileString() << endl;
    }

    file.close();

    return true;
}

const vector<User>& UserManager::getUsers() const
{
    return users;
}
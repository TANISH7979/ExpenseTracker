#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include <string>
#include "User.h"

class UserManager
{
private:
    std::vector<User> users;

public:
    UserManager();

    bool login(const std::string& email,
           const std::string& password);

int getUserId(const std::string& email);


bool registerUser(const User& user);

    const std::vector<User>& getUsers() const;
};


#endif
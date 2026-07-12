#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:
    int id;
    std::string username;
    std::string email;
    std::string password;

public:
    User();

    User(int id,
         const std::string& username,
         const std::string& email,
         const std::string& password);

    int getId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    std::string getPassword() const;

    void setId(int id);
    void setUsername(const std::string& username);
    void setEmail(const std::string& email);
    void setPassword(const std::string& password);

    std::string toFileString() const;

    static User fromFileString(const std::string& line);
};

#endif
#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:
    std::string username, password, pin;

public:
    bool registerUser();
    bool loginUser();
    std::string getUsername();
};

#endif
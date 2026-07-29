#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils
{
public:
    static std::string generatePassword(int len);
    static std::string checkStrength(std::string pass);
};

#endif
#include "Utils.h"
#include <cstdlib>

std::string Utils::generatePassword(int len)
{

    std::string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789!@#$%&*";

    std::string pass = "";

    for (int i = 0; i < len; i++)
    {
        pass += chars[rand() % chars.size()];
    }

    return pass;
}

std::string Utils::checkStrength(std::string pass)
{

    int score = 0;

    if (pass.length() >= 8)
        score++;
    if (pass.find_first_of("0123456789") != std::string::npos)
        score++;
    if (pass.find_first_of("!@#$%&*") != std::string::npos)
        score++;
    if (pass.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
        score++;

    if (score <= 1)
        return "Weak";
    else if (score == 2)
        return "Medium";
    return "Strong";
}
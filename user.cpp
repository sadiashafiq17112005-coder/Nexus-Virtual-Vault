#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool isStrongPassword(const std::string &pass)
{
    if (pass.length() < 6)
        return false;

    bool hasUpper = false, hasLower = false, hasDigit = false;

    for (char c : pass)
    {
        if (isupper(c))
            hasUpper = true;
        if (islower(c))
            hasLower = true;
        if (isdigit(c))
            hasDigit = true;
    }

    return hasUpper && hasLower && hasDigit;
}

bool User::registerUser()
{
    std::cout << "\n--- REGISTER ---\n";

    std::cout << "Enter Username: ";
    std::cin >> username;

    while (true)
    {
        std::cout << "Enter Password: ";
        std::cin >> password;

        if (!isStrongPassword(password))
        {
            std::cout << " Weak Password! (Use Upper + Lower + Digit)\n";
        }
        else
        {
            std::cout << "Strong Password\n";
            break;
        }
    }

    std::cout << "Enter PIN: ";
    std::cin >> pin;

    std::ofstream file("data/users.txt", std::ios::app);
    file << username << "|" << password << "|" << pin << "\n";
    file.close();

    std::cout << " Registered Successfully!\n";
    return true;
}

bool User::loginUser()
{
    std::cout << "\n--- LOGIN ---\n";

    int attempts = 3;

    while (attempts > 0)
    {

        std::string u, p, enteredPin;

        std::cout << "Enter Username: ";
        std::cin >> u;

        std::cout << "Show Password? (y/n): ";
        char opt;
        std::cin >> opt;

        std::cout << "Enter Password: ";
        std::cin >> p;

        if (opt == 'n')
        {
            std::cout << "Hidden: " << std::string(p.size(), '*') << "\n";
        }

        std::cout << "Enter PIN: ";
        std::cin >> enteredPin;

        std::ifstream file("data/users.txt");
        std::string line;

        while (getline(file, line))
        {
            std::stringstream ss(line);
            std::string fileUser, filePass, filePin;

            getline(ss, fileUser, '|');
            getline(ss, filePass, '|');
            getline(ss, filePin, '|');

            if (u == fileUser && p == filePass && enteredPin == filePin)
            {
                username = u;
                std::cout << " Login Successful!\n";
                return true;
            }
        }

        attempts--;

        if (attempts > 0)
        {
            std::cout << " Invalid Credentials! "
                      << attempts << " attempt(s) left.\n";
        }
        else
        {
            std::cout << " Too many failed attempts! System exiting...\n";
        }
    }

    return false;
}

std::string User::getUsername()
{
    return username;
}
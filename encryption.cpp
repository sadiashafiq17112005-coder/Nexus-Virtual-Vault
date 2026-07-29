#include "Encryption.h"
using namespace std;

// SAFE ENCRYPTION 

string encrypt(string data)
{

    string result = "";

    for (char c : data)
    {
        result += (char)((c + 3) % 126);
    }

    return result;
}

string decrypt(string data)
{

    string result = "";

    for (char c : data)
    {
        result += (char)((c - 3 + 126) % 126);
    }

    return result;
}
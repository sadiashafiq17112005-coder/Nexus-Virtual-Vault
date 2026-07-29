#ifndef ENTRY_H
#define ENTRY_H

#include <string>
using namespace std;

class VaultEntry
{
protected:
    string title, username, date;

public:
    VaultEntry(string t, string u, string d);
    virtual void display() = 0;
    virtual string serialize() = 0;
    virtual ~VaultEntry() {}
};

// PASSWORD
class PasswordEntry : public VaultEntry
{
    string password;

public:
    PasswordEntry(string t, string u, string p, string d);
    void display();
    string serialize();
};

// BANK
class BankingEntry : public VaultEntry
{
    string account, bank;

public:
    BankingEntry(string t, string u, string acc, string b, string d);
    void display();
    string serialize();
};

// NOTE
class SecureNote : public VaultEntry
{
    string note;

public:
    SecureNote(string t, string n, string d);
    void display();
    string serialize();
};

#endif
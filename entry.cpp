#include "Entry.h"
#include <iostream>

// BASE CLASS
VaultEntry::VaultEntry(string t, string u, string d)
{
    title = t;
    username = u;
    date = d;
}

// PASSWORD
PasswordEntry::PasswordEntry(string t, string u, string p, string d)
    : VaultEntry(t, u, d)
{
    password = p;
}

void PasswordEntry::display()
{
    cout << "\n========== PASSWORD ENTRY ==========\n";
    cout << "Title     : " << title << endl;
    cout << "Username  : " << username << endl;
    cout << "Password  : " << password << endl;
    cout << "Date      : " << date << endl;
}

string PasswordEntry::serialize()
{
    return "PASSWORD|" + title + "|" + username + "|" + password + "|" + date;
}

// BANK
BankingEntry::BankingEntry(string t, string u, string acc, string b, string d)
    : VaultEntry(t, u, d)
{
    account = acc;
    bank = b;
}

void BankingEntry::display()
{
    cout << "\n========== BANK ENTRY ==========\n";
    cout << "Title         : " << title << endl;
    cout << "Account Holder: " << username << endl;
    cout << "Account No    : " << account << endl;
    cout << "Bank          : " << bank << endl;
    cout << "Date          : " << date << endl;
}

string BankingEntry::serialize()
{
    return "BANK|" + title + "|" + username + "|" + account + "|" + bank + "|" + date;
}

// NOTE
SecureNote::SecureNote(string t, string n, string d)
    : VaultEntry(t, "", d)
{
    note = n;
}

void SecureNote::display()
{
    cout << "\n========== SECURE NOTE ==========\n";
    cout << "Title : " << title << endl;
    cout << "Note  : " << note << endl;
    cout << "Date  : " << date << endl;
}

string SecureNote::serialize()
{
    return "NOTE|" + title + "|" + note + "|" + date;
}
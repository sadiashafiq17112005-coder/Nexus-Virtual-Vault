#include "Vault.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "Encryption.h"
#include <limits>
using namespace std;
void logActivity(string action, string user, string title)
{

    ofstream log("data/activity_log.txt", ios::app);

    time_t now = time(0);
    string dt = ctime(&now);
    dt.pop_back();

    log << "[" << dt << "] "
        << user << " -> "
        << action << " : "
        << title << endl;
}

Vault::Vault(string username)
{
    currentUser = username;
    srand(time(0)); // Initialize random seed

    filename = "data/vault_" + username + ".txt"; //  MULTI USER FILE

    loadFromFile();
}

Vault::~Vault()
{
    for (auto e : entries)
        delete e;
}

// LOAD FROM FILE
void Vault::loadFromFile()
{

    entries.clear();

    ifstream file(filename);
    string line;

    while (getline(file, line))
    {

        if (line.empty())
            continue;

        // decrypt
        line = decrypt(line);

        stringstream ss(line);
        vector<string> tokens;
        string token;

        while (getline(ss, token, '|'))
        {
            tokens.push_back(token);
        }

        if (tokens.empty())
            continue;

        string type = tokens[0];

        // PASSWORD ENTRY
        if (type.find("PASSWORD") != string::npos && tokens.size() >= 5)
        {

            entries.push_back(
                new PasswordEntry(tokens[1], tokens[2], tokens[3], tokens[4]));
        }

        // NOTE ENTRY
        else if (type.find("NOTE") != string::npos && tokens.size() >= 4)
        {

            entries.push_back(
                new SecureNote(tokens[1], tokens[2], tokens[3]));
        }

        // BANK ENTRY
        else if (type.find("BANK") != string::npos && tokens.size() >= 6)
        {

            entries.push_back(
                new BankingEntry(tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]));
        }
    }

    file.close();
}
// SAVE TO FILE
void Vault::saveToFile()
{
    ofstream file(filename);

    for (auto e : entries)
    {
        string line = e->serialize();

        line = encrypt(line);

        file << line << endl;
    }
}

// PASSWORD GENERATOR
string Vault::generateStrongPassword()
{
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%";
    string pass = "";

    for (int i = 0; i < 12; i++)
    {
        pass += chars[rand() % chars.size()];
    }

    return pass;
}

// ADD ENTRY
void Vault::addEntry()
{

    int choice;

    cout << "\n1. Password\n2. Secure Note\n3. Banking\nChoice: ";
    cin >> choice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string title, username, password, note, acc, bank, date;

    cout << "Enter Title: ";
    getline(cin, title);

    cout << "Enter Date: ";
    getline(cin, date);

    if (choice == 1)
    {

        cout << "Enter Username: ";
        getline(cin, username);

        cout << "1. Enter Password\n2. Auto Generate\nChoice: ";
        int opt;
        cin >> opt;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opt == 2)
        {

            password = generateStrongPassword();
            cout << "Generated Password: " << password << endl;
        }
        else
        {

            cout << "Enter Password: ";
            getline(cin, password);

            while (password.empty())
            {
                cout << "Password cannot be empty. Enter again: ";
                getline(cin, password);
            }
        }

        entries.push_back(new PasswordEntry(title, username, password, date));
        logActivity("ADD PASSWORD", currentUser, title);
    }

    else if (choice == 2)
    {

        cout << "Enter Note: ";
        getline(cin, note);

        entries.push_back(new SecureNote(title, note, date));
        logActivity("ADD NOTE", currentUser, title);
    }

    else if (choice == 3)
    {

        cout << "Enter Account Holder: ";
        getline(cin, username);

        cout << "Enter Account Number: ";
        getline(cin, acc);

        cout << "Enter Bank Name: ";
        getline(cin, bank);

        entries.push_back(new BankingEntry(title, username, acc, bank, date));
        logActivity("ADD BANK", currentUser, title);
    }

    saveToFile();

    cout << "\nEntry Added Successfully!\n";
}
// VIEW ENTRIES
void Vault::viewEntries()
{

    cout << "\n========= VAULT =========\n";

    for (auto e : entries)
    {
        e->display();
        cout << "--------------------------\n";
    }
}

// SEARCH ENTRY
void Vault::searchEntry()
{

    string key;
    cout << "Enter Title to Search: ";
    cin.ignore();
    getline(cin, key);

    for (auto e : entries)
    {
        string data = e->serialize();

        if (data.find(key) != string::npos)
        {
            cout << "\nFound:\n";
            e->display();
            return;
        }
    }

    cout << "Not Found\n";
}

// DELETE ENTRY
void Vault::deleteEntry()
{

    string key;
    cout << "Enter Title to Delete: ";
    cin.ignore();
    getline(cin, key);

    for (int i = 0; i < entries.size(); i++)
    {

        if (entries[i]->serialize().find(key) != string::npos)
        {

            delete entries[i];
            entries.erase(entries.begin() + i);

            saveToFile();

            cout << "Deleted Successfully\n";
            logActivity("DELETE", currentUser, key);
            return;
        }
    }

    cout << "Not Found\n";
}

// UPDATE ENTRY
void Vault::updateEntry()
{

    string key;
    cout << "Enter Title to Update: ";
    cin.ignore();
    getline(cin, key);

    for (int i = 0; i < entries.size(); i++)
    {

        string data = entries[i]->serialize();

        if (data.find(key) != string::npos)
        {

            delete entries[i];
            entries.erase(entries.begin() + i);

            cout << "\nRe-enter Data:\n";

            addEntry();
            logActivity("UPDATE", currentUser, key);
            return;
        }
    }

    cout << "Not Found\n";
}
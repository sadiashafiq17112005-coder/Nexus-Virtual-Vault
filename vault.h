#ifndef VAULT_H
#define VAULT_H

#include <vector>
#include <string>
#include "Entry.h"

class Vault
{
private:
    std::vector<VaultEntry *> entries;
    std::string currentUser;
    std::string filename;

    void loadFromFile();
    void saveToFile();

public:
    Vault(std::string username);
    ~Vault();

    void addEntry();
    void viewEntries();
    void searchEntry();
    void deleteEntry();
    void updateEntry();

    std::string generateStrongPassword();
};

#endif
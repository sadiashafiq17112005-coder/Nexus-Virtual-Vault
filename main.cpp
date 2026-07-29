#include <iostream>
#include "User.h"
#include "Vault.h"

int main()
{

    User user;
    int choice;

    do
    {
        std::cout << "\n====== NEXUS VAULT ======\n";
        std::cout << "1. Register\n2. Login\n0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1)
        {
            user.registerUser();
        }

        else if (choice == 2)
        {
            if (user.loginUser())
            {

                Vault vault(user.getUsername());

                int opt;
                do
                {
                    std::cout << "\n--- VAULT MENU ---\n";
                    std::cout << "1. Add\n2. View\n3. Search\n4. Delete\n5. Update\n0. Logout\n";
                    std::cin >> opt;

                    switch (opt)
                    {
                    case 1:
                        vault.addEntry();
                        break;
                    case 2:
                        vault.viewEntries();
                        break;
                    case 3:
                        vault.searchEntry();
                        break;
                    case 4:
                        vault.deleteEntry();
                        break;
                    case 5:
                        vault.updateEntry();
                        break;
                    }

                } while (opt != 0);
            }
        }

    } while (choice != 0);

    return 0;
}
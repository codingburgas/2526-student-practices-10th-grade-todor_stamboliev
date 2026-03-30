#include <iostream>
#include <cstdlib>
#include "mainmenu.h" 

int main() {
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n========================================";
        std::cout << "\n     MOVIE TICKET BOOKING SYSTEM";
        std::cout << "\n========================================";
        std::cout << "\n  1. SEARCH MOVIES";
        std::cout << "\n  2. BOOK TICKETS";
        std::cout << "\n  3. ADMIN PANEL";
        std::cout << "\n  0. EXIT";
        std::cout << "\n========================================";
        std::cout << "\nENTER CHOICE: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            system("cls"); 
            continue;
        }
        system("cls");
        switch (choice) {
        case 1: searchMovies(); break;
        case 2: makeBooking();  break;
        case 3: adminPanel();   break;
        case 0: std::cout << "Goodbye!\n"; break;
        default: std::cout << "Invalid option!\n"; break;
        }

        if (choice != 0) {
            std::cout << "\n";
            system("pause");
            system("cls"); 
        }
    }
}


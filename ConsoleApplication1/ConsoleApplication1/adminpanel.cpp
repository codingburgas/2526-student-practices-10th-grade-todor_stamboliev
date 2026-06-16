#include <iostream>
#include <string>
#include "mainmenu.h"

void adminPanel() {
    int choice;
    std::cout << "\n--- Admin Panel ---\n";
    std::cout << "1. Add Movie\n";
    std::cout << "2. Delete Movie\n";
    std::cout << "3. Back to Main Menu\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;
    if (choice == 1) {
        std::string title, genre;
        int duration, year;

        std::cout << "\n--- Add Movie ---\n";
        std::cout << "Title: ";
        std::getline(std::cin >> std::ws, title);

        std::cout << "Genre: ";
        std::getline(std::cin >> std::ws, genre);

        std::cout << "Duration (in minutes): ";
        std::cin >> duration;

        std::cout << "Release Year: ";
        std::cin >> year;

        addMovieToList(title.c_str(), genre.c_str(), duration, year);
        std::cout << "\nMovie '" << title << "' added successfully!\n";

    }
    else if (choice == 2) {
        std::string toDelete;
        std::cout << "\n--- Delete Movie ---\n";
        std::cout << "Enter the title of the movie to delete: ";
        std::getline(std::cin >> std::ws, toDelete);
        deleteMovieFromList(toDelete); 

    }
    else if (choice == 3) {
        std::cout << "\nReturning to main menu...\n";
        return;
    }
    else {
        std::cout << "\nInvalid choice!\n";
    }
}
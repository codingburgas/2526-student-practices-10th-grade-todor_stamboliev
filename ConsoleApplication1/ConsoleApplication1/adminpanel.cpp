#include <iostream>
#include <string>
#include "mainmenu.h"

void adminPanel() {
    std::string title, genre;
    int duration, year;

    std::cout << "--- Admin Panel: Add Movie ---\n";

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
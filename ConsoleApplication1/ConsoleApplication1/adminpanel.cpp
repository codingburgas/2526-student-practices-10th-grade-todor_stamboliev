#include <iostream>
#include <string>
#include "cinema.h"

void adminPanel() {
    std::string newTitle;
    std::cout << "Enter movie title to add: ";
    std::getline(std::cin >> std::ws, newTitle); 

    movieDatabase.push_back({ newTitle });
    std::cout << "Movie added successfully!\n";
}
#include <iostream>
#include "cinema.h"

void makeBooking() {
    if (movieDatabase.empty()) {
        std::cout << "No movies available right now.\n";
        return;
    }

    std::cout << "Available movies:\n";
    for (int i = 0; i < movieDatabase.size(); i++) {
        std::cout << i + 1 << ". " << movieDatabase[i].title << "\n";
    }
}
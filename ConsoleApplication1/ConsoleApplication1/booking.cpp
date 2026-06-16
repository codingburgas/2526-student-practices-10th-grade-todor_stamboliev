#include <iostream>
#include <vector>
#include <string>
#include "mainmenu.h"

struct Movie {
    std::string title;
    std::string genre;
    int duration;
    int year;
};
static std::vector<Movie> movieDatabase;

void addMovieToList(const char* title, const char* genre, int duration, int year) {
    movieDatabase.push_back({ title, genre, duration, year });
}

void makeBooking() {
    if (movieDatabase.empty()) {
        std::cout << "\nNo movies available for booking.\n";
        return;
    }

    std::cout << "\n--- Available Movies ---\n";
    for (const auto& m : movieDatabase) {
        std::cout << "Title: " << m.title << std::endl;
        std::cout << "Year of release" << m.year << std::endl;
        std::cout << "Genre: " << m.genre << std::endl;
        std::cout << "Duration: " << m.duration << " min\n";
        std::cout << "--------------------------\n";
    }
}
void deleteMovieFromList(std::string titleToDelete) {
    for (size_t i = 0; i < movieDatabase.size(); i++) 
    {
        if (movieDatabase[i].title == titleToDelete) 
        {
            movieDatabase.erase(movieDatabase.begin() + i);
            std::cout << "\nMovie deleted successfully!\n";
            return; 
        }
    }
    std::cout << "\nMovie not found.\n";
}
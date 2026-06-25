#pragma once
#include <string>
#include <vector>

struct Movie {
    std::string title;
    std::string genre;
    int duration;
    int year;
};
extern std::vector<Movie> movieDatabase;

void addMovieToList(const char* title, const char* genre, int duration, int year);
void deleteMovieFromList(std::string titleToDelete);

void drawAdminPanel(int& currentState);
void drawBookingPanel(int& currentState);
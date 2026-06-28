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
enum UserRole { ROLE_GUEST, ROLE_CUSTOMER, ROLE_ADMIN };
extern UserRole currentUserRole;
void addMovieToList(const char* title, const char* genre, int duration, int year);
void deleteMovieFromList(std::string titleToDelete);
void drawAdminPanel(int& currentState);
void drawBookingPanel(int& currentState);
void drawLoginPanel(int& currentState);
void drawSearchBookingPanel(int& currentState);
void saveMoviesToFile();
void loadMoviesFromFile();
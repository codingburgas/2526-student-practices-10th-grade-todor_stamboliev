#pragma once
#include <string>
#include <vector>

const int SEAT_ROWS = 5;
const int SEAT_COLS = 6;

struct Movie {
    std::string title;
    std::string genre;
    int duration;
    int year;
    int seats[SEAT_ROWS][SEAT_COLS];    
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
void drawAdminSeatSelection(int& selectedIdx, bool& showAdminSeats);
#include "raylib.h"
#include "mainmenu.h"

std::vector<Movie> movieDatabase;

void addMovieToList(const char* title, const char* genre, int duration, int year) {
    movieDatabase.push_back({ title, genre, duration, year });
}

void deleteMovieFromList(std::string titleToDelete) {
    for (size_t i = 0; i < movieDatabase.size(); i++) {
        if (movieDatabase[i].title == titleToDelete) {
            movieDatabase.erase(movieDatabase.begin() + i);
            return;
        }
    }
}

void drawBookingPanel(int& currentState) {
    DrawRectangle(0, 0, 800, 140, DARKGRAY);
    DrawText("BOOK TICKETS", 300, 50, 36, LIGHTGRAY);

    DrawText("Booking options will appear here.", 240, 250, 20, DARKGRAY);

    Rectangle backBtn = { 250, 450, 300, 50 };
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), backBtn);

    DrawRectangleRec(backBtn, isHovered ? MAROON : GRAY);

    int textWidth = MeasureText("BACK TO MAIN MENU", 20);
    DrawText("BACK TO MAIN MENU", backBtn.x + (backBtn.width - textWidth) / 2, backBtn.y + 15, 20, WHITE);

    if (isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentState = 0;
    }
}
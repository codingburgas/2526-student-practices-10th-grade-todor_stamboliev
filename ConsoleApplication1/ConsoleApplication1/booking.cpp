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
    Vector2 mousePos = GetMousePosition();

    DrawRectangle(0, 0, 800, 100, DARKGRAY);
    DrawText("AVAILABLE MOVIES FOR BOOKING", 200, 35, 26, LIGHTGRAY);

    if (movieDatabase.empty()) {
        DrawText("No movies available for booking.", 250, 250, 20, DARKGRAY);
    }
    else {
        int startY = 130;
        for (size_t i = 0; i < movieDatabase.size(); i++) {
            DrawRectangle(50, startY, 700, 70, LIGHTGRAY);
            DrawRectangleLines(50, startY, 700, 70, DARKGRAY);

            DrawText(TextFormat("Title: %s", movieDatabase[i].title.c_str()), 70, startY + 15, 18, BLACK);
            DrawText(TextFormat("Genre: %s", movieDatabase[i].genre.c_str()), 70, startY + 40, 14, DARKGRAY);
            DrawText(TextFormat("Year: %d", movieDatabase[i].year), 450, startY + 15, 14, DARKGRAY);
            DrawText(TextFormat("Duration: %d min", movieDatabase[i].duration), 450, startY + 40, 14, DARKGRAY);

            startY += 85;
            if (startY > 440) break;
        }
    }

    Rectangle backBtn = { 250, 500, 300, 50 };
    bool hoverBack = CheckCollisionPointRec(mousePos, backBtn);
    DrawRectangleRec(backBtn, hoverBack ? BLACK : DARKGRAY);
    int textWidth = MeasureText("BACK TO MAIN MENU", 20);
    DrawText("BACK TO MAIN MENU", backBtn.x + (backBtn.width - textWidth) / 2, backBtn.y + 15, 20, WHITE);

    if (hoverBack && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentState = 0;
    }
}
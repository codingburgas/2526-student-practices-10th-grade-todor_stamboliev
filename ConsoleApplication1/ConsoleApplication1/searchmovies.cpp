#include "raylib.h"
#include "mainmenu.h"
#include <vector>
#include <string>
#include <algorithm>

extern std::vector<Movie> movieDatabase;

static char searchQuery[50] = "\0";
static int letterCount = 0;
static bool boxActive = false;

bool matchesSearch(const Movie& movie, const std::string& query) {
    if (query.empty()) return true;

    std::string titleLower = movie.title;
    std::string queryLower = query;

    std::transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);
    std::transform(queryLower.begin(), queryLower.end(), queryLower.begin(), ::tolower);

    return titleLower.find(queryLower) != std::string::npos;
}

void drawSearchBookingPanel(int& currentState) {
    Vector2 mousePos = GetMousePosition();
    Rectangle searchBox = { 130, 115, 620, 35 };

    if (CheckCollisionPointRec(mousePos, searchBox)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) boxActive = true;
    }
    else {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) boxActive = false;
    }

    if (boxActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letterCount < 48)) {
                searchQuery[letterCount] = (char)key;
                searchQuery[letterCount + 1] = '\0';
                letterCount++;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            searchQuery[letterCount] = '\0';
        }
    }

    DrawRectangle(0, 0, 800, 100, DARKGRAY);
    DrawText("SEARCH & BOOK MOVIES", 260, 35, 26, LIGHTGRAY);

    DrawText("Search:", 50, 120, 20, DARKGRAY);
    DrawRectangleRec(searchBox, LIGHTGRAY);
    DrawRectangleLinesEx(searchBox, 2, boxActive ? BLUE : DARKGRAY);

    if (letterCount == 0) {
        DrawText("Click here and type movie title...", 140, 123, 18, GRAY);
    }
    else {
        DrawText(searchQuery, 140, 123, 18, BLACK);
    }

    int startY = 175;
    int displayedMovies = 0;
    for (size_t i = 0; i < movieDatabase.size(); i++) {
        if (matchesSearch(movieDatabase[i], searchQuery)) {
            DrawRectangle(50, startY, 700, 70, LIGHTGRAY);
            DrawRectangleLines(50, startY, 700, 70, DARKGRAY);

            DrawText(TextFormat("Title: %s", movieDatabase[i].title.c_str()), 70, startY + 15, 18, BLACK);
            DrawText(TextFormat("Genre: %s", movieDatabase[i].genre.c_str()), 70, startY + 40, 14, DARKGRAY);
            DrawText(TextFormat("Year: %d", movieDatabase[i].year), 450, startY + 15, 14, DARKGRAY);
            DrawText(TextFormat("Duration: %d min", movieDatabase[i].duration), 450, startY + 40, 14, DARKGRAY);

            startY += 85;
            displayedMovies++;

            if (startY > 440) break;
        }
    }
    if (displayedMovies == 0) {
        if (letterCount == 0) {
            DrawText("No movies available for booking.", 250, 280, 20, DARKGRAY);
        }
        else {
            DrawText("No movies found matching your search.", 220, 280, 20, DARKGRAY);
        }
    }

    Rectangle backBtn = { 250, 530, 300, 50 };
    bool hoverBack = CheckCollisionPointRec(mousePos, backBtn);
    DrawRectangleRec(backBtn, hoverBack ? BLACK : DARKGRAY);
    int textWidth = MeasureText("BACK TO MAIN MENU", 20);
    DrawText("BACK TO MAIN MENU", backBtn.x + (backBtn.width - textWidth) / 2, backBtn.y + 15, 20, WHITE);

    if (hoverBack && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        searchQuery[0] = '\0';
        letterCount = 0;
        boxActive = false;
        currentState = 0;
    }
}
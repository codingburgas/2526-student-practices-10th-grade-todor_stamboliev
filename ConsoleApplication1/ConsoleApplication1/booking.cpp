#include "raylib.h"
#include "mainmenu.h"
#include <fstream> 
#include <string> 

std::vector<Movie> movieDatabase;

int selectedMovieIndex = -1;
bool showingSeats = false;

void saveMoviesToFile() {
    std::ofstream outFile("movies.txt");
    if (outFile.is_open()) {
        for (const auto& movie : movieDatabase) {
            outFile << movie.title << "\n";
            outFile << movie.genre << "\n";
            outFile << movie.duration << "\n";
            outFile << movie.year << "\n";

            for (int r = 0; r < SEAT_ROWS; r++) {
                for (int c = 0; c < SEAT_COLS; c++) {
                    int state = (movie.seats[r][c] == 1) ? 0 : movie.seats[r][c];
                    outFile << state << " ";
                }
            }
            outFile << "\n";
        }
        outFile.close();
    }
}

void loadMoviesFromFile() {
    movieDatabase.clear();
    std::ifstream inFile("movies.txt");
    if (inFile.is_open()) {
        Movie movie;
        std::string durationStr, yearStr;

        while (std::getline(inFile, movie.title) &&
            std::getline(inFile, movie.genre) &&
            std::getline(inFile, durationStr) &&
            std::getline(inFile, yearStr)) {

            if (durationStr.empty() || yearStr.empty()) continue;

            try {
                movie.duration = std::stoi(durationStr);
                movie.year = std::stoi(yearStr);
            }
            catch (...) {
                continue;
            }

            for (int r = 0; r < SEAT_ROWS; r++) {
                for (int c = 0; c < SEAT_COLS; c++) {
                    inFile >> movie.seats[r][c];
                }
            }
            inFile.ignore();
            movieDatabase.push_back(movie);
        }
        inFile.close();
    }
}

void addMovieToList(const char* title, const char* genre, int duration, int year) {
    Movie newMovie;
    newMovie.title = title;
    newMovie.genre = genre;
    newMovie.duration = duration;
    newMovie.year = year;

    for (int r = 0; r < SEAT_ROWS; r++) {
        for (int c = 0; c < SEAT_COLS; c++) {
            newMovie.seats[r][c] = 0;
        }
    }

    movieDatabase.push_back(newMovie);
    saveMoviesToFile();
}

void deleteMovieFromList(std::string titleToDelete) {
    for (size_t i = 0; i < movieDatabase.size(); i++) {
        if (movieDatabase[i].title == titleToDelete) {
            movieDatabase.erase(movieDatabase.begin() + i);
            saveMoviesToFile();
            return;
        }
    }
}

void drawSeatSelection(int& currentState) {
    Vector2 mousePos = GetMousePosition();
    Movie& movie = movieDatabase[selectedMovieIndex];

    DrawRectangle(0, 0, 800, 100, DARKGRAY);
    DrawText(TextFormat("SEATS FOR: %s", movie.title.c_str()), 50, 35, 24, LIGHTGRAY);

    DrawRectangle(200, 120, 400, 20, MAROON);
    DrawText("SCREEN", 375, 123, 14, WHITE);

    int startX = 220;
    int startY = 180;
    int seatSize = 45;
    int gap = 15;
    bool mouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    for (int r = 0; r < SEAT_ROWS; r++) {
        DrawText(TextFormat("Row %d", r + 1), startX - 70, startY + r * (seatSize + gap) + 15, 16, DARKGRAY);

        for (int c = 0; c < SEAT_COLS; c++) {
            Rectangle seatRect = {
                (float)(startX + c * (seatSize + gap)),
                (float)(startY + r * (seatSize + gap)),
                (float)seatSize,
                (float)seatSize
            };

            Color seatColor = GREEN;
            if (movie.seats[r][c] == 1) seatColor = YELLOW;
            else if (movie.seats[r][c] == 2) seatColor = RED;

            DrawRectangleRec(seatRect, seatColor);
            DrawRectangleLinesEx(seatRect, 1, BLACK);
            DrawText(TextFormat("%d", c + 1), seatRect.x + 18, seatRect.y + 15, 14, BLACK);

            if (mouseClicked && CheckCollisionPointRec(mousePos, seatRect)) {
                if (movie.seats[r][c] == 0) {
                    movie.seats[r][c] = 1;
                }
                else if (movie.seats[r][c] == 1) {
                    movie.seats[r][c] = 0;
                }
            }
        }
    }

    bool hasSelectedSeats = false;
    for (int r = 0; r < SEAT_ROWS; r++) {
        for (int c = 0; c < SEAT_COLS; c++) {
            if (movie.seats[r][c] == 1) {
                hasSelectedSeats = true;
            }
        }
    }

    if (hasSelectedSeats) {
        Rectangle confirmBtn = { 420, 510, 200, 45 };
        bool hoverConfirm = CheckCollisionPointRec(mousePos, confirmBtn);
        DrawRectangleRec(confirmBtn, hoverConfirm ? DARKGREEN : GREEN);
        DrawText("CONFIRM BOOKING", confirmBtn.x + 20, confirmBtn.y + 15, 16, WHITE);

        if (hoverConfirm && mouseClicked) {
            for (int r = 0; r < SEAT_ROWS; r++) {
                for (int c = 0; c < SEAT_COLS; c++) {
                    if (movie.seats[r][c] == 1) movie.seats[r][c] = 2;
                }
            }
            saveMoviesToFile();
            showingSeats = false;
        }
    }

    Rectangle backBtn = { 180, 510, 200, 45 };
    bool hoverBack = CheckCollisionPointRec(mousePos, backBtn);
    DrawRectangleRec(backBtn, hoverBack ? BLACK : DARKGRAY);
    DrawText("BACK", backBtn.x + 75, backBtn.y + 15, 16, WHITE);

    if (hoverBack && mouseClicked) {
        for (int r = 0; r < SEAT_ROWS; r++) {
            for (int c = 0; c < SEAT_COLS; c++) {
                if (movie.seats[r][c] == 1) movie.seats[r][c] = 0;
            }
        }
        showingSeats = false;
    }
}

void drawBookingPanel(int& currentState) {
    if (showingSeats && selectedMovieIndex != -1) {
        drawSeatSelection(currentState);
        return;
    }

    Vector2 mousePos = GetMousePosition();

    DrawRectangle(0, 0, 800, 100, DARKGRAY);
    DrawText("AVAILABLE MOVIES FOR BOOKING", 200, 35, 26, LIGHTGRAY);

    if (movieDatabase.empty()) {
        DrawText("No movies available for booking.", 250, 250, 20, DARKGRAY);
    }
    else {
        int startY = 130;
        for (size_t i = 0; i < movieDatabase.size(); i++) {
            Rectangle movieRow = { 50, (float)startY, 700, 70 };
            bool hoverRow = CheckCollisionPointRec(mousePos, movieRow);

            DrawRectangleRec(movieRow, hoverRow ? LIGHTGRAY : RAYWHITE);
            DrawRectangleLines(50, startY, 700, 70, DARKGRAY);

            DrawText(TextFormat("Title: %s", movieDatabase[i].title.c_str()), 70, startY + 15, 18, BLACK);
            DrawText(TextFormat("Genre: %s", movieDatabase[i].genre.c_str()), 70, startY + 40, 14, DARKGRAY);
            DrawText(TextFormat("Year: %d", movieDatabase[i].year), 450, startY + 15, 14, DARKGRAY);
            DrawText(TextFormat("Duration: %d min", movieDatabase[i].duration), 450, startY + 40, 14, DARKGRAY);

            if (hoverRow && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                selectedMovieIndex = i;
                showingSeats = true;
            }

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

void drawAdminSeatSelection(int& selectedIdx, bool& showAdminSeats) {
    Vector2 mousePos = GetMousePosition();
    if (selectedIdx < 0 || selectedIdx >= (int)movieDatabase.size()) {
        showAdminSeats = false;
        return;
    }

    DrawRectangle(0, 0, 800, 100, DARKGRAY);
    DrawText(TextFormat("MANAGE SEATS: %s", movieDatabase[selectedIdx].title.c_str()), 50, 35, 24, LIGHTGRAY);
    DrawRectangle(200, 120, 400, 20, MAROON);
    DrawText("SCREEN", 375, 123, 14, WHITE);

    int startX = 220;
    int startY = 180;
    int seatSize = 45;
    int gap = 15;
    bool mouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    bool databaseChanged = false;

    for (int r = 0; r < SEAT_ROWS; r++) {
        DrawText(TextFormat("Row %d", r + 1), startX - 70, startY + r * (seatSize + gap) + 15, 16, DARKGRAY);
        for (int c = 0; c < SEAT_COLS; c++) {
            Rectangle seatRect = {
                (float)(startX + c * (seatSize + gap)),
                (float)(startY + r * (seatSize + gap)),
                (float)seatSize,
                (float)seatSize
            };

            Color seatColor = GREEN;
            if (movieDatabase[selectedIdx].seats[r][c] == 2) seatColor = RED;

            DrawRectangleRec(seatRect, seatColor);
            DrawRectangleLinesEx(seatRect, 1, BLACK);
            DrawText(TextFormat("%d", c + 1), seatRect.x + 18, seatRect.y + 15, 14, BLACK);

            if (mouseClicked && CheckCollisionPointRec(mousePos, seatRect)) {
                if (movieDatabase[selectedIdx].seats[r][c] == 2) {
                    movieDatabase[selectedIdx].seats[r][c] = 0;
                    databaseChanged = true;
                }
            }
        }
    }

    if (databaseChanged) {
        saveMoviesToFile();
    }

    Rectangle backBtn = { 300, 510, 200, 45 };
    bool hoverBack = CheckCollisionPointRec(mousePos, backBtn);
    DrawRectangleRec(backBtn, hoverBack ? BLACK : DARKGRAY);
    DrawText("BACK", backBtn.x + 75, backBtn.y + 15, 16, WHITE);
    if (hoverBack && mouseClicked) {
        showAdminSeats = false;
    }
}
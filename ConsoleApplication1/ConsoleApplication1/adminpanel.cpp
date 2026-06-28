#include "raylib.h"
#include "mainmenu.h"
#include <cstring>
#include <cstdlib>
#include <string>

void drawAdminPanel(int& currentState) {
    static char titleBuf[32] = "\0";
    static char genreBuf[32] = "\0";
    static char durationBuf[10] = "\0";
    static char yearBuf[10] = "\0";
    static char deleteBuf[32] = "\0";

    static int activeField = 0;
    static const char* statusMessage = "";
    static bool showAdminSeats = false;

    int foundMovieIdx = -1;
    if (strlen(deleteBuf) > 0) {
        for (size_t i = 0; i < movieDatabase.size(); i++) {
            if (movieDatabase[i].title == std::string(deleteBuf)) {
                foundMovieIdx = (int)i;
                break;
            }
        }
    }

    if (showAdminSeats && foundMovieIdx != -1) {
        drawAdminSeatSelection(foundMovieIdx, showAdminSeats);
        return;
    }
    else if (showAdminSeats && foundMovieIdx == -1) {
        showAdminSeats = false;
    }

    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mousePos, { 150, 150, 200, 35 })) activeField = 1;
        else if (CheckCollisionPointRec(mousePos, { 150, 210, 200, 35 })) activeField = 2;
        else if (CheckCollisionPointRec(mousePos, { 150, 270, 200, 35 })) activeField = 3;
        else if (CheckCollisionPointRec(mousePos, { 150, 330, 200, 35 })) activeField = 4;
        else if (CheckCollisionPointRec(mousePos, { 480, 150, 200, 35 })) activeField = 5;
        else activeField = 0;
    }

    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125)) {
            if (activeField == 1 && strlen(titleBuf) < 30) { int len = strlen(titleBuf); titleBuf[len] = (char)key; titleBuf[len + 1] = '\0'; }
            if (activeField == 2 && strlen(genreBuf) < 30) { int len = strlen(genreBuf); genreBuf[len] = (char)key; genreBuf[len + 1] = '\0'; }
            if (activeField == 3 && strlen(durationBuf) < 5 && key >= '0' && key <= '9') { int len = strlen(durationBuf); durationBuf[len] = (char)key; durationBuf[len + 1] = '\0'; }
            if (activeField == 4 && strlen(yearBuf) < 4 && key >= '0' && key <= '9') { int len = strlen(yearBuf); yearBuf[len] = (char)key; yearBuf[len + 1] = '\0'; }
            if (activeField == 5 && strlen(deleteBuf) < 30) { int len = strlen(deleteBuf); deleteBuf[len] = (char)key; deleteBuf[len + 1] = '\0'; }
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (activeField == 1 && strlen(titleBuf) > 0) titleBuf[strlen(titleBuf) - 1] = '\0';
        if (activeField == 2 && strlen(genreBuf) > 0) genreBuf[strlen(genreBuf) - 1] = '\0';
        if (activeField == 3 && strlen(durationBuf) > 0) durationBuf[strlen(durationBuf) - 1] = '\0';
        if (activeField == 4 && strlen(yearBuf) > 0) yearBuf[strlen(yearBuf) - 1] = '\0';
        if (activeField == 5 && strlen(deleteBuf) > 0) deleteBuf[strlen(deleteBuf) - 1] = '\0';
    }

    DrawRectangle(0, 0, 800, 100, DARKGRAY);
    DrawText("ADMIN PANEL", 320, 35, 30, LIGHTGRAY);

    DrawText("ADD NEW MOVIE", 100, 110, 20, MAROON);

    DrawText("Title:", 50, 158, 16, DARKGRAY);
    DrawRectangleRec({ 150, 150, 200, 35 }, activeField == 1 ? LIGHTGRAY : RAYWHITE);
    DrawRectangleLines(150, 150, 200, 35, DARKGRAY);
    DrawText(titleBuf, 160, 158, 16, BLACK);

    DrawText("Genre:", 50, 218, 16, DARKGRAY);
    DrawRectangleRec({ 150, 210, 200, 35 }, activeField == 2 ? LIGHTGRAY : RAYWHITE);
    DrawRectangleLines(150, 210, 200, 35, DARKGRAY);
    DrawText(genreBuf, 160, 218, 16, BLACK);

    DrawText("Duration:", 50, 278, 16, DARKGRAY);
    DrawRectangleRec({ 150, 270, 200, 35 }, activeField == 3 ? LIGHTGRAY : RAYWHITE);
    DrawRectangleLines(150, 270, 200, 35, DARKGRAY);
    DrawText(durationBuf, 160, 278, 16, BLACK);

    DrawText("Year:", 50, 338, 16, DARKGRAY);
    DrawRectangleRec({ 150, 330, 200, 35 }, activeField == 4 ? LIGHTGRAY : RAYWHITE);
    DrawRectangleLines(150, 330, 200, 35, DARKGRAY);
    DrawText(yearBuf, 160, 338, 16, BLACK);

    Rectangle addBtn = { 150, 390, 200, 40 };
    bool hoverAdd = CheckCollisionPointRec(mousePos, addBtn);
    DrawRectangleRec(addBtn, hoverAdd ? MAROON : GRAY);
    DrawText("SAVE MOVIE", 200, 400, 16, WHITE);

    if (hoverAdd && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (strlen(titleBuf) > 0 && strlen(genreBuf) > 0) {
            bool alreadyExists = false;
            for (const auto& movie : movieDatabase) {
                if (movie.title == std::string(titleBuf)) {
                    alreadyExists = true;
                    break;
                }
            }

            if (alreadyExists) {
                statusMessage = "Error: Movie already exists!";
            }
            else {
                addMovieToList(titleBuf, genreBuf, atoi(durationBuf), atoi(yearBuf));
                statusMessage = "Movie added successfully!";
                titleBuf[0] = genreBuf[0] = durationBuf[0] = yearBuf[0] = '\0';
            }
        }
        else {
            statusMessage = "Error: Fill all fields!";
        }
    }

    DrawText("MANAGE / DELETE MOVIE", 480, 110, 20, MAROON);
    DrawText("Title:", 400, 158, 16, DARKGRAY);
    DrawRectangleRec({ 480, 150, 200, 35 }, activeField == 5 ? LIGHTGRAY : RAYWHITE);
    DrawRectangleLines(480, 150, 200, 35, DARKGRAY);
    DrawText(deleteBuf, 490, 158, 16, BLACK);

    if (foundMovieIdx != -1) {
        Rectangle editSeatsBtn = { 480, 200, 200, 35 };
        bool hoverEdit = CheckCollisionPointRec(mousePos, editSeatsBtn);
        DrawRectangleRec(editSeatsBtn, hoverEdit ? ORANGE : GRAY);
        DrawText("MANAGE SEATS", 530, 210, 16, WHITE);

        if (hoverEdit && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            showAdminSeats = true;
        }

        Rectangle delBtn = { 480, 245, 200, 35 };
        bool hoverDel = CheckCollisionPointRec(mousePos, delBtn);
        DrawRectangleRec(delBtn, hoverDel ? RED : MAROON);
        DrawText("DELETE MOVIE", 530, 255, 16, WHITE);

        if (hoverDel && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            deleteMovieFromList(deleteBuf);
            statusMessage = "Movie removed successfully!";
            deleteBuf[0] = '\0';
        }
    }
    else if (strlen(deleteBuf) > 0) {
        DrawText("Movie not found!", 480, 200, 16, RED);
    }

    DrawText(statusMessage, 150, 450, 18, DARKGRAY);

    Rectangle backBtn = { 250, 500, 300, 50 };
    bool hoverBack = CheckCollisionPointRec(mousePos, backBtn);
    DrawRectangleRec(backBtn, hoverBack ? BLACK : DARKGRAY);
    int textWidth = MeasureText("BACK TO MAIN MENU", 20);
    DrawText("BACK TO MAIN MENU", backBtn.x + (backBtn.width - textWidth) / 2, backBtn.y + 15, 20, WHITE);

    if (hoverBack && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        statusMessage = "";
        deleteBuf[0] = '\0';
        currentState = 0;
    }
}
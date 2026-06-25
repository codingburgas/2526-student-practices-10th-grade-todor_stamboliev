#include "raylib.h"
#include "mainmenu.h"

struct Button {
    Rectangle rect;
    const char* text;
    int targetState;
    bool isExit;
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Movie Ticket Booking System");
    SetTargetFPS(60);

    int currentState = 0;

    Button buttons[] = {
        { { 250, 220, 300, 50 }, "1. SEARCH MOVIES", 1, false },
        { { 250, 300, 300, 50 }, "2. BOOK TICKETS", 2, false },
        { { 250, 380, 300, 50 }, "3. ADMIN PANEL", 3, false },
        { { 250, 460, 300, 50 }, "0. EXIT", 0, true }
    };
    int buttonCount = sizeof(buttons) / sizeof(buttons[0]);

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        if (currentState == 0) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                for (int i = 0; i < buttonCount; i++) {
                    if (CheckCollisionPointRec(mousePos, buttons[i].rect)) {
                        if (buttons[i].isExit) {
                            goto close;
                        }
                        currentState = buttons[i].targetState;
                        break;
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentState == 0) {
            DrawRectangle(0, 0, screenWidth, 140, DARKGRAY);

            int title1Width = MeasureText("MOVIE TICKET", 36);
            int title2Width = MeasureText("BOOKING SYSTEM", 34);

            DrawText("MOVIE TICKET", (screenWidth - title1Width) / 2, 30, 36, LIGHTGRAY);
            DrawText("BOOKING SYSTEM", (screenWidth - title2Width) / 2, 75, 34, LIGHTGRAY);

            for (int i = 0; i < buttonCount; i++) {
                bool isHovered = CheckCollisionPointRec(mousePos, buttons[i].rect);
                Color btnColor = isHovered ? MAROON : GRAY;
                DrawRectangleRec(buttons[i].rect, btnColor);

                int textWidth = MeasureText(buttons[i].text, 20);
                int textX = buttons[i].rect.x + (buttons[i].rect.width - textWidth) / 2;
                int textY = buttons[i].rect.y + (buttons[i].rect.height - 20) / 2;
                DrawText(buttons[i].text, textX, textY, 20, WHITE);
            }
        }
        else if (currentState == 3) {
            drawAdminPanel(currentState);
        }
        else if (currentState == 2) {
            drawBookingPanel(currentState);
        }
        else if (currentState == 1) {
            currentState = 0;
        }

        EndDrawing();
    }

close:
    CloseWindow();
    return 0;
}
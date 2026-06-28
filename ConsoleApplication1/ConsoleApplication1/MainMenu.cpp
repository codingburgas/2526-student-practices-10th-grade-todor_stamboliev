#include "raylib.h"
#include "mainmenu.h"
#include <string> // Осигурява безпроблемна работа на std::string

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

    loadMoviesFromFile();

    int currentState = 0;
    float securityMessageTimer = 0.0f;

    Button buttons[] = {
        { { 250, 180, 300, 50 }, "1. SEARCH MOVIES", 1, false },
        { { 250, 250, 300, 50 }, "2. BOOK TICKETS", 2, false },
        { { 250, 320, 300, 50 }, "3. ADMIN PANEL", 3, false },
        { { 250, 390, 300, 50 }, "4. LOGIN", 4, false },
        { { 250, 460, 300, 50 }, "0. EXIT", 0, true }
    };
    int buttonCount = sizeof(buttons) / sizeof(buttons[0]);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        Vector2 mousePos = GetMousePosition();

        if (securityMessageTimer > 0.0f) {
            securityMessageTimer -= deltaTime;
        }

        if (currentState == 0) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                for (int i = 0; i < buttonCount; i++) {
                    if (CheckCollisionPointRec(mousePos, buttons[i].rect)) {
                        if (buttons[i].isExit) {
                            goto close;
                        }

                        if (buttons[i].targetState == 3 && currentUserRole != ROLE_ADMIN) {
                            securityMessageTimer = 3.0f;
                        }
                        else {
                            currentState = buttons[i].targetState;
                        }
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

            if (securityMessageTimer > 0.0f) {
                const char* alert = "ACCESS REJECTED: Admin account verification required!";
                int textW = MeasureText(alert, 16);
                DrawText(alert, (screenWidth - textW) / 2, 530, 16, RED);
            }

            if (currentUserRole != ROLE_GUEST) {
                std::string statusText = "Active User: " + std::string(currentUserRole == ROLE_ADMIN ? "Admin" : "Customer");
                DrawText(statusText.c_str(), 15, 150, 14, DARKGREEN);
            }
        }
        else if (currentState == 4) {
            drawLoginPanel(currentState);
        }
        else if (currentState == 3) {
            if (currentUserRole != ROLE_ADMIN) currentState = 0;
            else drawAdminPanel(currentState);
        }
        else if (currentState == 2) {
            drawBookingPanel(currentState);
        }
        else if (currentState == 1) {
            drawSearchBookingPanel(currentState);
        }

        EndDrawing();
    }

close:
    CloseWindow();
    return 0;
}
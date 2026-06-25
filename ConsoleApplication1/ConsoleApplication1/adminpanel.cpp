#include "raylib.h"
#include "mainmenu.h"

void drawAdminPanel(int& currentState) {
    DrawRectangle(0, 0, 800, 140, DARKGRAY);
    DrawText("ADMIN PANEL", 300, 50, 36, LIGHTGRAY);

    DrawText("Admin options will appear here.", 240, 250, 20, DARKGRAY);

    Rectangle backBtn = { 250, 450, 300, 50 };
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), backBtn);

    DrawRectangleRec(backBtn, isHovered ? MAROON : GRAY);

    int textWidth = MeasureText("BACK TO MAIN MENU", 20);
    DrawText("BACK TO MAIN MENU", backBtn.x + (backBtn.width - textWidth) / 2, backBtn.y + 15, 20, WHITE);

    if (isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentState = 0;
    }
}
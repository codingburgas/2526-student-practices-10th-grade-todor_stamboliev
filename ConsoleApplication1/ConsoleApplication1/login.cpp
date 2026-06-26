#include "raylib.h"
#include "mainmenu.h"
#include <string>

UserRole currentUserRole = ROLE_GUEST;

struct LoginField {
    Rectangle bounds;
    std::string text;
    int maxChars;
    bool isFocused;
};

static LoginField usernameField = { { 250, 240, 300, 40 }, "", 15, true };
static LoginField passwordField = { { 250, 320, 300, 40 }, "", 15, false };
static std::string loginErrorMessage = "";

void drawLoginPanel(int& currentState) {
    Vector2 mousePos = GetMousePosition();
    Rectangle backBtn = { 410, 390, 140, 40 };

    if (currentUserRole != ROLE_GUEST) {
        DrawRectangle(0, 0, 800, 140, DARKGRAY);
        int titleW = MeasureText("ACTIVE SESSION", 34);
        DrawText("ACTIVE SESSION", (800 - titleW) / 2, 50, 34, LIGHTGRAY);

        std::string welcomeMsg = "Logged in as: " + std::string(currentUserRole == ROLE_ADMIN ? "ADMINISTRATOR" : "CUSTOMER");
        DrawText(welcomeMsg.c_str(), (800 - MeasureText(welcomeMsg.c_str(), 18)) / 2, 240, 18, DARKGRAY);

        Rectangle logoutBtn = { 250, 300, 300, 40 };
        bool hoverLogout = CheckCollisionPointRec(mousePos, logoutBtn);
        DrawRectangleRec(logoutBtn, hoverLogout ? MAROON : GRAY);
        int logoutTextW = MeasureText("LOG OUT", 18);
        DrawText("LOG OUT", logoutBtn.x + (logoutBtn.width - logoutTextW) / 2, logoutBtn.y + 11, 18, WHITE);

        bool hoverBack = CheckCollisionPointRec(mousePos, backBtn);
        DrawRectangleRec(backBtn, hoverBack ? MAROON : GRAY);
        int backTextW = MeasureText("BACK", 18);
        DrawText("BACK", backBtn.x + (backBtn.width - backTextW) / 2, backBtn.y + 11, 18, WHITE);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(mousePos, logoutBtn)) {
                currentUserRole = ROLE_GUEST;
                loginErrorMessage = "";
            }
            if (CheckCollisionPointRec(mousePos, backBtn)) {
                currentState = 0;
            }
        }
        return;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        usernameField.isFocused = CheckCollisionPointRec(mousePos, usernameField.bounds);
        passwordField.isFocused = CheckCollisionPointRec(mousePos, passwordField.bounds);
    }

    LoginField* activeField = nullptr;
    if (usernameField.isFocused) activeField = &usernameField;
    else if (passwordField.isFocused) activeField = &passwordField;

    if (activeField != nullptr) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (activeField->text.length() < activeField->maxChars)) {
                activeField->text += (char)key;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !activeField->text.empty()) {
            activeField->text.pop_back();
        }

        if (IsKeyPressed(KEY_TAB)) {
            usernameField.isFocused = !usernameField.isFocused;
            passwordField.isFocused = !passwordField.isFocused;
        }
    }

    Rectangle loginBtn = { 250, 390, 140, 40 };
    bool loginTriggered = false;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mousePos, loginBtn)) loginTriggered = true;
        if (CheckCollisionPointRec(mousePos, backBtn)) {
            usernameField.text = "";
            passwordField.text = "";
            loginErrorMessage = "";
            currentState = 0;
            return;
        }
    }
    if (IsKeyPressed(KEY_ENTER)) loginTriggered = true;

    if (loginTriggered) {
        if (usernameField.text.empty() || passwordField.text.empty()) {
            loginErrorMessage = "Fields cannot be blank!";
        }
        else if (usernameField.text == "admin@cinema.bg" && passwordField.text == "admin1234") {
            currentUserRole = ROLE_ADMIN;
            usernameField.text = "";
            passwordField.text = "";
            loginErrorMessage = "";
            currentState = 3;
        }
        else if (passwordField.text == "1234") {
            currentUserRole = ROLE_CUSTOMER;
            usernameField.text = "";
            passwordField.text = "";
            loginErrorMessage = "";
            currentState = 0;
        }
        else {
            loginErrorMessage = "Invalid Account Username or Password!";
            passwordField.text = "";
        }
    }

    DrawRectangle(0, 0, 800, 140, DARKGRAY);
    int titleWidth = MeasureText("SYSTEM SIGN-IN PORTAL", 34);
    DrawText("SYSTEM SIGN-IN PORTAL", (800 - titleWidth) / 2, 50, 34, LIGHTGRAY);

    DrawText("Email:", usernameField.bounds.x, usernameField.bounds.y - 22, 16, DARKGRAY);
    DrawText("Password:", passwordField.bounds.x, passwordField.bounds.y - 22, 16, DARKGRAY);

    DrawRectangleRec(usernameField.bounds, LIGHTGRAY);
    DrawRectangleLinesEx(usernameField.bounds, 2, usernameField.isFocused ? MAROON : GRAY);
    DrawText(usernameField.text.c_str(), usernameField.bounds.x + 10, usernameField.bounds.y + 11, 18, BLACK);

    DrawRectangleRec(passwordField.bounds, LIGHTGRAY);
    DrawRectangleLinesEx(passwordField.bounds, 2, passwordField.isFocused ? MAROON : GRAY);
    std::string maskedPass(passwordField.text.length(), '*');
    DrawText(maskedPass.c_str(), passwordField.bounds.x + 10, passwordField.bounds.y + 11, 18, BLACK);

    bool hoverLogin = CheckCollisionPointRec(mousePos, loginBtn);
    DrawRectangleRec(loginBtn, hoverLogin ? MAROON : GRAY);
    int loginTextW = MeasureText("LOG IN", 18);
    DrawText("LOG IN", loginBtn.x + (loginBtn.width - loginTextW) / 2, loginBtn.y + 11, 18, WHITE);

    bool hoverBack = CheckCollisionPointRec(mousePos, backBtn);
    DrawRectangleRec(backBtn, hoverBack ? MAROON : GRAY);
    int backTextW = MeasureText("CANCEL", 18);
    DrawText("CANCEL", backBtn.x + (backBtn.width - backTextW) / 2, backBtn.y + 11, 18, WHITE);

    if (!loginErrorMessage.empty()) {
        int errW = MeasureText(loginErrorMessage.c_str(), 16);
        DrawText(loginErrorMessage.c_str(), (800 - errW) / 2, 460, 16, RED);
    }
}
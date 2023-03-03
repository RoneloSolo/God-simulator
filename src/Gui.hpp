#include "raylib.h"

bool isPaintingOpen = false;

const int32_t MAX_COLORS_COUNT = 23;
int colorMouseHover = 0;
int colorSelected = 0;
    
Color colors[MAX_COLORS_COUNT] = {
    RAYWHITE, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN,
    SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN,
    LIGHTGRAY, GRAY, DARKGRAY, BLACK };


Rectangle colorsRecs[MAX_COLORS_COUNT] = { 0 };


void InitGui() {
    for (int i = 0; i < MAX_COLORS_COUNT; i++) {
        colorsRecs[i].x = 10 + 30.0f*i + 2*i;
        colorsRecs[i].y = 10;
        colorsRecs[i].width = 30;
        colorsRecs[i].height = 30;
    }
}

void DrawGui() {
    if(!isPaintingOpen) return;

    // Draw top panel
    DrawRectangle(0, 0, GetScreenWidth(), 50, RAYWHITE);
    DrawLine(0, 50, GetScreenWidth(), 50, LIGHTGRAY);

    // Draw colors
    for (int i = 0; i < MAX_COLORS_COUNT; i++) DrawRectangleRec(colorsRecs[i], colors[i]);

    // Draw selection borders
    DrawRectangleLinesEx((Rectangle){ colorsRecs[colorSelected].x - 2, colorsRecs[colorSelected].y - 2, colorsRecs[colorSelected].width + 4, colorsRecs[colorSelected].height + 4 }, 2, BLACK);

    // Draw hover
    DrawRectangleRec(colorsRecs[colorMouseHover], Fade(WHITE, 0.6f));
}

void UpdateGui() {
    if(IsKeyPressed(KEY_G)) isPaintingOpen = !isPaintingOpen;

    Vector2 mousePoint = GetMousePosition();
    for (int i = 0; i < MAX_COLORS_COUNT; i++) {
        if (CheckCollisionPointRec(mousePoint, colorsRecs[i])) {
            colorMouseHover = i;
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                colorSelected = colorMouseHover;
            }
            return;
        }
    }
}
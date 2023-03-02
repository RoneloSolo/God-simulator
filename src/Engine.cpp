#include "Engine.h"
#include "MapGenerator.h"
#include <iostream>

static Texture texture;

static const double PHYSICS_UPDATE_TIME =  0.2;
static double lastPhysicsTime = 0;

Engine::Engine(int width, int height, const char* title) {
    scaledWidth = width / scale;
    scaledHeight = height / scale;

/*======================Initialize-Raylib-Window===============================*/

    SetTargetFPS(60);
    InitWindow(width, height, title);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);

/*=============================================================================*/

    texture = GenerateMap(GetRandomValue(-99999, 99999), GetRandomValue(-99999, 99999));
}

Engine::~Engine() noexcept {
    CloseWindow();
}

bool Engine::Close() const {
    return WindowShouldClose();
}

void Engine::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

/*==================================Drawing====================================*/

    DrawTextureEx(texture, Vector2{0, 0}, 0, scale, WHITE);

/*=============================================================================*/

    EndDrawing();
}

void Engine::Update() {
    if(IsKeyPressed(KEY_SPACE)) texture = GenerateMap(GetRandomValue(-99999, 99999), GetRandomValue(-99999, 99999));
}

void Engine::PhysicsUpdate(){
    double time = GetTime();
    if(time < lastPhysicsTime + PHYSICS_UPDATE_TIME) return;
    lastPhysicsTime = time;
/*==============================PhysicsUpdate===================================*/
/*=============================================================================*/
}

// Dont touch this
void Engine::Tick() {
    Draw();
    Update();
    PhysicsUpdate();
}
#include "Engine.hpp"
#include "MapGenerator.hpp"
#include <iostream>
#include "System.hpp"
#include "Gui.hpp"

static Texture texture;

static entt::registry registry;
static System ecsSystem;

static int32_t entitiesCount = 0;
static const int32_t MAX_ENTITIES = 1000;

static const double PHYSICS_UPDATE_TIME =  0.2;
static double lastPhysicsTime = 0;

static Vector2 mousePos;

Engine::Engine(int width, int height, const char* title) {
    scaledWidth = width / scale;
    scaledHeight = height / scale;

    SetTargetFPS(60);
    InitWindow(width, height, title);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);

/*======================Initialize Here==========================================*/
    
    InitGui();
    texture = GenerateMap(GetRandomValue(-99999, 99999), GetRandomValue(-99999, 99999));
    // ecsSystem.CreateNpc(registry);

/*==============================================================================*/
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

    // ecsSystem.Draw(registry);5
    DrawGui();
    DrawFPS(0, 50);

/*=============================================================================*/

    EndDrawing();
}

void Engine::Update() {
/*==================================Update====================================*/
    mousePos = Vector2{GetMousePosition().x / scale, GetMousePosition().y / scale};
    
    if(IsKeyPressed(KEY_SPACE)) texture = GenerateMap(GetRandomValue(-99999, 99999), GetRandomValue(-99999, 99999));

    UpdateGui();
    
    // ecsSystem.Move(registry);
    // ecsSystem.Input(registry);

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

        Image image = LoadImageFromTexture(texture);
        int32_t stroke = 1;
        int32_t amountOfPixels = stroke * stroke;
        
        for(int x = 0; x < stroke; x++) {
            for(int y = 0; y < stroke; y++) {
                ImageDrawPixel(&image, mousePos.x - stroke/2 + x, mousePos.y - stroke/2 + y, colors[colorSelected]);
            }
        }

        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

/*=====================================================================================*/
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
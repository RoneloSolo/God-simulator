#include "Engine.hpp"
#include "MapGenerator.hpp"
#include <iostream>
#include "System.hpp"

static Texture texture;

static entt::registry registry;
static System ecsSystem;

static int32_t entitiesCount = 0;

static const double PHYSICS_UPDATE_TIME =  0.2;
static double lastPhysicsTime = 0;

Engine::Engine(int width, int height, const char* title) {
    scaledWidth = width / scale;
    scaledHeight = height / scale;

    SetTargetFPS(60);
    InitWindow(width, height, title);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);

/*======================Initialize Here==========================================*/

    texture = GenerateMap(GetRandomValue(-99999, 99999), GetRandomValue(-99999, 99999));

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

    ecsSystem.Draw(registry);

    DrawText(TextFormat("entities count: %d", entitiesCount), 0, 0, 24, BLACK);
    DrawFPS(0, 50);


/*=============================================================================*/

    EndDrawing();
}

void Engine::Update() {
/*==================================Update====================================*/

    if(IsKeyPressed(KEY_SPACE)) texture = GenerateMap(GetRandomValue(-99999, 99999), GetRandomValue(-99999, 99999));

    if(IsKeyPressed(KEY_S)) {
        for(int i = 0; i < 1000; i++) {
            auto entity = registry.create();

            Vector2 pos = Vector2{(float)GetRandomValue(-1000, 1000), (float)GetRandomValue(-1000, 1000)};
            Vector2 scale = Vector2{(float)GetRandomValue(1, 50), (float)GetRandomValue(1, 50)};
            Color color = Color{(unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255};

            Vector2 vel = Vector2{(float)GetRandomValue(-1,1), (float)GetRandomValue(-1,1)};
            registry.emplace<Transform2D>(entity, pos, scale, 0);
            registry.emplace<KinematicBody2D>(entity, vel);
            registry.emplace<Sprite2D>(entity, color);
        }
        entitiesCount += 1000;
    }

    if(IsKeyPressed(KEY_A)) {
        for(int i = 0; i < 10000; i++) {
            auto entity = registry.create();

            Vector2 pos = Vector2{(float)GetRandomValue(-1000, 1000), (float)GetRandomValue(-1000, 1000)};
            Vector2 scale = Vector2{(float)GetRandomValue(1, 50), (float)GetRandomValue(1, 50)};
            Color color = Color{(unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255};

            Vector2 vel = Vector2{(float)GetRandomValue(-1,1), (float)GetRandomValue(-1,1)};
            registry.emplace<Transform2D>(entity, pos, scale, 0);
            registry.emplace<KinematicBody2D>(entity, vel);
            registry.emplace<Sprite2D>(entity, color);
        }
        entitiesCount += 10000;
    }

    ecsSystem.Move(registry);

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
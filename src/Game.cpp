#include "raylib.h"
#include "Game.h"
#include <stdlib.h>
#include <iostream>

static const int scale = 5;
static int _width;
static int _height;
static Texture texture;
static Vector2 position;

void GenerateMap(){
    Image image = GenImagePerlinNoise(_width, _height, position.x, position.y, scale);
    Color *pixels = LoadImageColors(image);

    // Turn black and white perlin noise to colores
    for (int y = 0; y < _height; y++){
        for (int x = 0; x < _width; x++){
            int i = (int)pixels[y*_width + x].r;
            if(i < 65){
                pixels[y*_width + x] = Color{4, 0 ,95, 255};
            }
            else if(i < 85){
                pixels[y*_width + x] = Color{50, 94 ,190, 255};
            }
            else if(i < 100){
                pixels[y*_width + x] = Color{152, 191 ,245, 255};
            }
            else if(i < 125){
                pixels[y*_width + x] = Color{179, 224 ,123, 255};
            }
            else if(i < 200){
                pixels[y*_width + x] = Color{124, 188 ,45, 255};
            }
            else if(i < 225){
                pixels[y*_width + x] = Color{140, 125 ,134, 255};
            }
            else{
                pixels[y*_width + x] = Color{212, 202 ,208, 255};
            }
        }
    }

    image = {
        .data = pixels,       
        .width = _width,
        .height = _height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    texture = LoadTextureFromImage(image);
    UnloadImage(image); 
}

Game::Game(int width, int height, const char* title){
    _width = width / scale;
    _height = height / scale;
    SetTargetFPS(60);
    InitWindow(width, height, title);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    GenerateMap();
}

Game::~Game() noexcept{
    CloseWindow();
}

bool Game::Close() const{
    return WindowShouldClose();
}

void Game::Draw(){
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTextureEx(texture, Vector2{ 0, 0}, 0, scale, WHITE);
    EndDrawing();
}

void Game::Update(){
    // if (IsKeyDown(KEY_RIGHT)) position.x += 2.0f;
    // if (IsKeyDown(KEY_LEFT)) position.x -= 2.0f;
    // if (IsKeyDown(KEY_UP)) position.y -= 2.0f;
    // if (IsKeyDown(KEY_DOWN)) position.y += 2.0f;
    // GenerateMap();
}

void Game::Tick(){
    Draw();
    Update();
}
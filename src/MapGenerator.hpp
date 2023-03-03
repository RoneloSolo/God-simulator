#include "raylib.h"
#include "raymath.h"

static const int scale = 5;
static int scaledWidth;
static int scaledHeight;

enum BlockType {
    DEEPWATER = 5,
    WATER = 45,
    SAND = 50,
    GRASS = 125,
    ROCK = 175,
    SNOW = 255,
};

// return int from 0 - 255, create fall off map.
int FallOffMap(int x, int y) {
    float i = x / (float)scaledWidth * 2 - 1;
    float j = y / (float)scaledHeight * 2 - 1;
    return fmaxf(abs(i),abs(j)) * 255;
}

// Create the map to texture offsetX offsetY the offsets of the perlin noise.
Texture GenerateMap(int offsetX, int offsetY) {
    Image image = GenImagePerlinNoise(scaledWidth, scaledHeight, offsetX, offsetY, scale);
    Color *pixels = LoadImageColors(image);

    for (int y = 0; y < scaledHeight; y++) {
        for (int x = 0; x < scaledWidth; x++){
            int i = (int)pixels[y*scaledWidth + x].r;

            i -= FallOffMap(x, y); 

/*============================Colors===========================================*/

            if(i < DEEPWATER) {
                pixels[y*scaledWidth + x] = Color{23, 36, 49, 255};
            }
            else if(i < WATER) {
                pixels[y*scaledWidth + x] = BLUE;
            }
            else if(i < SAND) {
                pixels[y*scaledWidth + x] = Color{194, 178, 128, 255};
            }
            else if(i < GRASS ){
                pixels[y*scaledWidth + x] = Color{124, 252, 0, 255};
            }
            else if(i < ROCK) {
                pixels[y*scaledWidth + x] = Color{90, 77, 65, 255};
            }
            else if(i < SNOW) {
                pixels[y*scaledWidth + x] = Color{255, 250, 250, 255};
            }

/*=============================================================================*/
        }
    }

    image = {
        .data = pixels,       
        .width = scaledWidth,
        .height = scaledHeight,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    Texture texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}
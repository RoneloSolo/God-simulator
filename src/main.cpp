#include "Engine.hpp"

int main(void) {
    Engine engine{1920, 1080, "Ant-simulator"};
    while (!engine.Close()) {
        engine.Tick();
    }
    engine.Close();
    return 0;
}
#include "../include/entt.hpp"
#include "raylib.h"

class System {
    public:
        void Move(entt::registry &registry);
        void Draw(entt::registry &registry);
        void CreateNpc(entt::registry &registry);
        void Input(entt::registry &registry);
};

// position, scale, rotation
struct Transform2D {
    Vector2 position;
    Vector2 scale;
    float rotation;
};
// velocity, friction, gravity
struct KinematicBody2D {
    Vector2 velocity;
    float friction;
    float gravity;
};
struct Destination {
    Vector2 target;
};

struct Sprite2D {
    Color color;
};

void System::Move(entt::registry &registry) {
    auto view = registry.view<Transform2D, KinematicBody2D, Destination>();

    for (auto [entity, transform, kinematicBody, destination]: view.each()) {

        // if(transform.position.x > 1920) kinematicBody.velocity.x = -kinematicBody.velocity.x;
        // else if(transform.position.x < 0) kinematicBody.velocity.x = -kinematicBody.velocity.x;
        
        // if(transform.position.y > 1080) kinematicBody.velocity.y = -kinematicBody.velocity.y;
        // else if(transform.position.y < 0) kinematicBody.velocity.y = -kinematicBody.velocity.y;

        kinematicBody.velocity = Vector2Normalize(Vector2Subtract(destination.target ,transform.position));

        transform.position = Vector2{kinematicBody.velocity.x + transform.position.x, kinematicBody.velocity.y + transform.position.y};
        transform.position.x = Wrap(transform.position.x, 0, 1920);
        transform.position.y = Wrap(transform.position.y, 0, 1080);
    }
}

void System::Draw(entt::registry &registry) {
    auto view = registry.view<Transform2D, Sprite2D>();
    for (auto [entity, transform, sprite]: view.each()) {
        DrawRectangle(transform.position.x, transform.position.y, transform.scale.x, transform.scale.y, sprite.color);
    }
}

void System::Input(entt::registry &registry) {
    auto view = registry.view<KinematicBody2D, Destination>();
    for (auto [entity,kinematicBody ,destination]: view.each()) {
        if(!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) continue;
        destination.target = GetMousePosition();
    }
}

void System::CreateNpc(entt::registry &registry) {
    auto entity = registry.create();

    Vector2 pos{1920/2, 1080/2};
    Vector2 scale{50, 50};
    Color color{RAYWHITE};

    registry.emplace<Transform2D>(entity, pos, scale, 0);
    registry.emplace<KinematicBody2D>(entity, Vector2{0, 0});
    registry.emplace<Sprite2D>(entity, color);
    registry.emplace<Destination>(entity, Vector2{0 ,0});
}
#include "../include/entt.hpp"
#include "raylib.h"

class System {
    public:
        virtual void Move(entt::registry &registry);
        virtual void Draw(entt::registry &registry);
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

struct Sprite2D {
    Color color;
};

void System::Move(entt::registry &registry) {
    auto view = registry.view<Transform2D, KinematicBody2D>();

    for (auto [entity, transform, kinematicBody]: view.each()) {
        transform.position = Vector2{kinematicBody.velocity.x + transform.position.x, kinematicBody.velocity.y + transform.position.y};

        if(transform.position.x > 1920) kinematicBody.velocity.x = -kinematicBody.velocity.x;
        else if(transform.position.x < 0) kinematicBody.velocity.x = -kinematicBody.velocity.x;
        
        if(transform.position.y > 1080) kinematicBody.velocity.y = -kinematicBody.velocity.y;
        else if(transform.position.y < 0) kinematicBody.velocity.y = -kinematicBody.velocity.y;
    }
}

void System::Draw(entt::registry &registry) {
    auto view = registry.view<Transform2D, Sprite2D>();
    for (auto [entity, transform, sprite]: view.each()) {
        // auto &npc  = view.get<Transform2D, Sprite2D>(entity);
        DrawRectangle(transform.position.x, transform.position.y, transform.scale.x, transform.scale.y, sprite.color);
    }
}
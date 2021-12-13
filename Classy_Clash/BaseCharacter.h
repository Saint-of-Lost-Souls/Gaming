#include "raylib.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRec();

    virtual void tick(float deltaTime);
    
protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    Vector2 screenPos{};
    // 1- facing right, -1 facing left
    float rightLeft{1.f};
    float runningTime{0.0};
    int frame{};
    int maxFrame{6};
    float width{};
    float height{};
    float updateTime{1.f / 12.f};
    float speed{4.f};
   float scale{4.f};
   Vector2 velocity{};
};


#endif
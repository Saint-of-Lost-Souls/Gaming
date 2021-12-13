#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) // Constructor
{
    width = texture.width / maxFrame;
    height = texture.height;

    // Center of the window :: scale:: sprite size
    screenPos = {
        static_cast<float>(winWidth) / 2.f - scale * (0.5f * width),
        static_cast<float>(winHeight) / 2.f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{    
    
    Vector2 velocity{};
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;
    BaseCharacter::tick(deltaTime);
    // Set worldPos = worldPos - direction
    
}

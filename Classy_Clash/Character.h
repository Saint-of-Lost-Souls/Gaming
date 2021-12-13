#include "raylib.h"
#include "BaseCharacter.h"


#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight); // Constructor
    virtual void tick(float deltaTime) override;
    Vector2 getScreenPos{};

private:
};

#endif
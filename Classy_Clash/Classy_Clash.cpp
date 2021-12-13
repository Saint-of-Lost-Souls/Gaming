#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    const int winWidth{512};
    const int winHeight{512};
    InitWindow(winWidth, winHeight, "Icy RPG");

    Texture2D map = LoadTexture("Classy.png");
    Vector2 mapPos{0.0, 0.0};
    Vector2 pos{};
    const float mapScale{2.f};

    Character knight{winWidth, winHeight}; // Create a character variable
    Enemy goblin{
        Vector2{0.f, 0.f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
        };
    // Make an array of props    
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")},
    };

    goblin.setTarget(&knight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // Draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());

        //  Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + winWidth > map.width * mapScale ||
            knight.getWorldPos().y + winHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }
        goblin.tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow();
    UnloadTexture(map);
}
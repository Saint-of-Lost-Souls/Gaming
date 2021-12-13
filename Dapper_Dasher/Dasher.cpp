#include "raylib.h" // external library
#include <cstdio>   // standard library

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // Update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        if (data.frame > maxFrame)
        // Update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    int winDimensions[2];
    winDimensions[0] = 510;
    winDimensions[1] = 380;

    InitWindow(winDimensions[0], winDimensions[1], "Dapper Dasher");

    // Acceleration due to gravity
    const int gravity{1'000}; // (pixels/second) /second
    int velocity{10};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};

    // Scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = winDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = winDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.runningTime = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    //Jumping
    bool isJumping{};
    const int jumpVel{600}; // pixels per second
    int jumpCount{2};
    int doubleJump{1};

    // Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    const int sizeOfNebulae = 6;
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.x = winDimensions[0] + i * 400;
        nebulae[i].pos.y = winDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0;
        nebulae[i].updateTime = 1.0 / 12.0;
    }

    float finishLine{nebulae[sizeOfNebulae - 1].pos.x};
    int nebVel = -300;

    bool collision{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta time = time since last frame
        const float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(BLACK);

        // Reset background
        bgX -= 20 * dT;
        if (bgX <= -background.width * 2) bgX = 0.0;        
        mgX -= 80 * dT;
        if (mgX <= -midground.width * 2) mgX = 0.0;        
        fgX -= 150 * dT;
        if (fgX <= -foreground.width * 2) fgX = 0.0;
        

        // Draw background
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width * 2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        // Draw midground
        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX + midground.width * 2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        // Draw foreground
        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX + foreground.width * 2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        // Jump check
        if (isOnGround(scarfyData, winDimensions[1]))
        {
            velocity = 0;
            isJumping = false;
            jumpCount = 2;
        }
        else
        {
            velocity += gravity * dT;
            isJumping = true;
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            if (!isJumping)
            {
                velocity -= jumpVel;
            }
            if (isJumping && jumpCount > doubleJump)
            {
                velocity -= jumpVel / 2;
                jumpCount--;
            }
        }

        // Update sprite position
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebVel * dT;
        }
        finishLine += nebVel * dT;

        scarfyData.pos.y += velocity * dT;

        // Update sprite animation
        if (!isJumping)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        
        for (AnimData nebula : nebulae)
        {
            float pad{45};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2 * pad,
                nebula.rec.height - 2 * pad};
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height};
            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }

        if (collision)
        {
            DrawText("You lose(r)!", winDimensions[0] / 3.3, winDimensions[1] / 2, 40, BLUE);
            DrawText("You lose(r)!", winDimensions[0] / 3.7, winDimensions[1] / 2, 40, RED);
            DrawText("You lose(r)!", winDimensions[0] / 3.5, winDimensions[1] / 2, 40, WHITE);

        }
        else if (scarfyData.pos.x >= finishLine)  
        {
            DrawText("You win!", winDimensions[0] / 3.5, winDimensions[1] / 2, 40, WHITE);
        }
        
        else
        {
            for (int i = 0; i < sizeOfNebulae; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }

        // Drawing sprites

        EndDrawing();
    }

    // Game logic ends

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);

    CloseWindow();
}

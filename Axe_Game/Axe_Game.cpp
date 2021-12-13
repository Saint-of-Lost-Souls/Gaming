#include "raylib.h" // external library
#include <cstdio>   // standard library

int main()
{
    // Window dimensions
    int width{800};
    int height{450};
    InitWindow(width, height, "Shade's Secret Window");

    // Circle coordinates
    int circle_X{200};
    int circle_Y{200};
    int circle_radius{25};

    // Circle edges
    int l_circle_X{circle_X - circle_radius};
    int r_circle_X{circle_X + circle_radius};
    int u_circle_Y{circle_Y - circle_radius};
    int b_circle_Y{circle_Y + circle_radius};

    // Axe coordinates
    int axe_X{400};
    int axe_Y{0};
    int axe_length{50};

    // Axe edges
    int l_axe_X{axe_X};
    int r_axe_X{axe_X + axe_length};
    int u_axe_Y{axe_Y};
    int b_axe_Y{axe_Y + axe_length};

    int direction{10};

    bool collisionWithAxe =
        (b_axe_Y >= u_circle_Y) &&
        (u_axe_Y <= b_circle_Y) &&
        (l_axe_X <= r_circle_X) &&
        (r_axe_X >= l_circle_X);

    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Game logic begins

        if (collisionWithAxe)
        {
            DrawText("Game Over!", 325, 200, 30, RED);
        }
        else
        {
            // Update circle edges
            l_circle_X = circle_X - circle_radius;
            r_circle_X = circle_X + circle_radius;
            u_circle_Y = circle_Y - circle_radius;
            b_circle_Y = circle_Y + circle_radius;

            // Update axe edges
            l_axe_X = axe_X;
            r_axe_X = axe_X + axe_length;
            u_axe_Y = axe_Y;
            b_axe_Y = axe_Y + axe_length;

            // Update collision with axe
            collisionWithAxe =
                (b_axe_Y >= u_circle_Y) &&
                (u_axe_Y <= b_circle_Y) &&
                (l_axe_X <= r_circle_X) &&
                (r_axe_X >= l_circle_X);

            DrawCircle(circle_X, circle_Y, circle_radius, WHITE);
            DrawRectangle(axe_X, axe_Y, axe_length, axe_length, RED);

            // Move the axe
            axe_Y += direction;
            if (axe_Y > height || axe_Y < 0)
            {
                direction = -direction;
            }

            if (IsKeyDown(KEY_D) && circle_X < width)
            {
                circle_X += 10;
            }
            if (IsKeyDown(KEY_A) && circle_X > 0)
            {
                circle_X -= 10;
            }
            if (IsKeyDown(KEY_W) && circle_Y > 0)
            {
                circle_Y -= 10;
            }
            if (IsKeyDown(KEY_S) && circle_Y < height)
            {
                circle_Y += 10;
            }
        }

        // Game logic ends
        EndDrawing();
    }
}

/*   int milesToDisneyland{10};

    do
    {
        printf("Are we there yet?\n");
        milesToDisneyland--;
    } while (milesToDisneyland > 0); */

/* DrawRectangle(10, 10, width - 20, height - 20, WHITE);
        DrawRectangle(15, 15, width - 30, height - 30, BLACK);
        DrawRectangle(25, 25, width - 50, height - 50, WHITE);
        DrawRectangle(30, 30, width - 60, height - 60, BLACK);
        DrawRectangle(40, 40, width - 80, height - 80, WHITE);
        DrawRectangle(45, 45, width - 90, height - 90, BLACK);
        DrawRectangle(55, 55, width - 110, height - 110, WHITE);
        DrawRectangle(60, 60, width - 120, height - 120, BLACK);
        DrawRectangle(70, 70, width - 140, height - 140, WHITE);
        DrawRectangle(75, 75, width - 150, height - 150, BLACK);        
        DrawCircle(100, 50, 35, PURPLE);
        DrawCircle(300, 75, 10, BLUE);
        DrawCircle(250, 15, 40, YELLOW);
        DrawCircle(150, 200, 55, GREEN);
        DrawText("Shade", circle_X, circle_Y, 32, BLUE);
        */
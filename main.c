#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <raylib.h>

void randomize(bool *color, int *direction, int *orientation) {
    if (rand() % 3 == 0) { *color = !*color; }
    *direction = rand() & 0b11;
    *orientation = rand() & 0b11;
}

int main(void) {
    InitWindow(1920, 1080, "Ebb and Flow");
    SetTargetFPS(60);

    const int speed = 10;

    srand(time(0));
    bool color = (rand() & 0b1) == 0; // effectively rand % 2
    // int direction = rand() & 0b11; // where it is moving
    int direction = 0;
    int orientation = rand() & 0b11; // where it is facing
    int x = 0;
    int y = 0;

    while (!WindowShouldClose()) {
        switch (direction) {
            case 0:
                x += speed;
                break;
            case 1:
                y += speed;
                break;
            case 2:
                x -= speed;
                break;
            case 3:
                y -= speed;
                break;
        }
        // if (x > 0) x -= 96 * 5;
        // if (y < -54 * 4) y += 54 * 4;
        x %= 1920 / 4;
        y %= 1080 / 5;

        if (IsKeyPressed(KEY_RIGHT)) { printf("right\n"); randomize(&color, &direction, &orientation); }
        if (IsKeyPressed(KEY_LEFT)) { printf("left\n"); randomize(&color, &direction, &orientation); }
        if (IsKeyPressed(KEY_UP)) { printf("up\n"); randomize(&color, &direction, &orientation); }
        if (IsKeyPressed(KEY_DOWN)) { printf("down\n"); randomize(&color, &direction, &orientation); }

        BeginDrawing();

        ClearBackground(DARKBLUE);

        for (int i = 0; i < 56; i++) {
            int ix = x + (i % 7 - 1) * 1920 / 4;
            int iy = y + (i / 7 - 1) * 1080 / 5;
            DrawCircle(ix, iy, 100, color ? GREEN : ORANGE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

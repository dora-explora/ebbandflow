#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <raylib.h>
#include <wchar.h>

void randomize(bool *color, int *direction, int *orientation) {
    if (rand() % 3 == 0) { *color = !*color; }
    *direction = rand() & 0b11;
    *orientation = rand() & 0b11;
}

bool check_input(int input, bool color, int direction, int orientation, int *score, int *goodness, int *badness) {
    bool result = false;
    if (color) {
        if (input == direction) {
            result = true;
        }
    } else {
        if (input == orientation) {
            result = true;
        }
    }
    if (result) {
        *score += 1;
        *goodness = 15;
    } else {
        *badness = 15;
    }
    return result;
}

int main(void) {
    InitWindow(1920, 1080, "Ebb and Flow");
    SetTargetFPS(60);

    const int speed = 10;

    srand(time(0));
    bool color = (rand() & 0b1) == 0; // effectively rand % 2
    // int direction = rand() & 0b11; // where it is moving
    int direction = 3;
    // int orientation = rand() & 0b11; // where it is facing
    int orientation = 3;
    int x = 0;
    int y = 0;

    int score = 0;
    int goodness = 0;
    int badness = 0;

    Image greenup = LoadImage("assets/greenleaf.png");
    Image greenright = LoadImage("assets/greenleaf.png");
    Image greendown = LoadImage("assets/greenleaf.png");
    Image greenleft = LoadImage("assets/greenleaf.png");
    Image orangeup = LoadImage("assets/orangeleaf.png");
    Image orangeright = LoadImage("assets/orangeleaf.png");
    Image orangedown = LoadImage("assets/orangeleaf.png");
    Image orangeleft = LoadImage("assets/orangeleaf.png");

    ImageRotate(&greenright, 90);
    ImageRotate(&greendown, 180);
    ImageRotate(&greenleft, 270);
    ImageRotate(&orangeright, 90);
    ImageRotate(&orangedown, 180);
    ImageRotate(&orangeleft, 270);

    Texture textures[8] = {};
    textures[0] = LoadTextureFromImage(greenup);
    textures[1] = LoadTextureFromImage(greenright);
    textures[2] = LoadTextureFromImage(greendown);
    textures[3] = LoadTextureFromImage(greenleft);
    textures[4] = LoadTextureFromImage(orangeup);
    textures[5] = LoadTextureFromImage(orangeright);
    textures[6] = LoadTextureFromImage(orangedown);
    textures[7] = LoadTextureFromImage(orangeleft);

    while (!WindowShouldClose()) {
        switch (direction) {
            case 0:
                y -= speed;
                break;
            case 1:
                x += speed;
                break;
            case 2:
                y += speed;
                break;
            case 3:
                x -= speed;
                break;
        }
        // if (x > 0) x -= 96 * 5;
        // if (y < -54 * 4) y += 54 * 4;
        x %= 1920 / 4;
        y %= 1080 / 5;

        if (IsKeyPressed(KEY_UP)) { check_input(0, color, direction, orientation, &score, & goodness, &badness); randomize(&color, &direction, &orientation);  }
        if (IsKeyPressed(KEY_RIGHT)) { check_input(1, color, direction, orientation, &score, & goodness, &badness); randomize(&color, &direction, &orientation);  }
        if (IsKeyPressed(KEY_DOWN)) { check_input(2, color, direction, orientation, &score, & goodness, &badness); randomize(&color, &direction, &orientation);  }
        if (IsKeyPressed(KEY_LEFT)) { check_input(3, color, direction, orientation, &score, & goodness, &badness); randomize(&color, &direction, &orientation);  }

        Color bgcolor = (Color) {0, 30, 90, 255};

        if (goodness > 0) {
           bgcolor.g += goodness * 5;
           goodness--;
        }
        if (badness > 0) {
           bgcolor.r += badness * 10;
           badness--;
        }

        BeginDrawing();

        ClearBackground(bgcolor);

        for (int i = 0; i < 56; i++) {
            int ix = x + (i % 7 - 1) * 1920 / 4;
            int iy = y + (i / 7 - 1) * 1080 / 5;
            DrawTexture(textures[orientation + color * 4], ix, iy, WHITE);
        }

        DrawText(TextFormat("Score: %i", score), 10, 10, 60, WHITE);

        EndDrawing();
    }

    // UnloadTexture(greenleaf);
    // UnloadTexture(orangeleaf);
    CloseWindow();
    return 0;
}

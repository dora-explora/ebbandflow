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

bool check_input(int input, bool color, int direction, int orientation, int *score, int *attempts, int *goodness, int *badness) {
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
    *attempts += 1;
    return result;
}

int main(void) {
    InitWindow(1920, 1080, "Ebb and Flow");
    SetTargetFPS(60);

    const int speed = 10;

    srand(time(NULL));
    bool color = (rand() & 0b1) == 0; // effectively rand % 2
    int direction = rand() & 0b11; // where it is moving
    int orientation = rand() & 0b11; // where it is facing
    int x = 1920/10;
    int y = 0;

    int score = 0;
    int attempts = 0;
    int goodness = 0;
    int badness = 0;
    bool playing = false;

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

    uint32_t start;

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

        Color bgcolor = (Color) {0, 30, 90, 255};
        Color tint = WHITE;

        if (!playing) {
            bgcolor = (Color) {0, 15, 45, 255};
            tint = GRAY;
            if (IsKeyPressed(KEY_ENTER)) {
                score = 0;
                attempts = 0;
                start = time(NULL);
                randomize(&color, &direction, &orientation);
                playing = true;
            }
        }
        else {
            if (IsKeyPressed(KEY_UP)) { check_input(0, color, direction, orientation, &score, &attempts, &goodness, &badness); randomize(&color, &direction, &orientation);  }
            if (IsKeyPressed(KEY_RIGHT)) { check_input(1, color, direction, orientation, &score, &attempts, &goodness, &badness); randomize(&color, &direction, &orientation);  }
            if (IsKeyPressed(KEY_DOWN)) { check_input(2, color, direction, orientation, &score, &attempts, &goodness, &badness); randomize(&color, &direction, &orientation);  }
            if (IsKeyPressed(KEY_LEFT)) { check_input(3, color, direction, orientation, &score, &attempts, &goodness, &badness); randomize(&color, &direction, &orientation);  }
            if (goodness > 0) {
               bgcolor.g += goodness * 5;
               goodness--;
            }
            if (badness > 0) {
               bgcolor.r += badness * 10;
               badness--;
            }
        }

        int timeleft = 30 - time(NULL) + start;
        if (timeleft <= 0) {
            playing = false;
        }


        BeginDrawing();

        ClearBackground(bgcolor);

        if (playing) DrawText(TextFormat("%01d", timeleft), 900, 490, 100, GRAY);

        for (int i = 0; i < 56; i++) {
            int ix = x + (i % 7 - 1) * 1920 / 4;
            int iy = y + (i / 7 - 1) * 1080 / 5;
            DrawTexture(textures[orientation + color * 4], ix, iy, tint);
        }

        if (!playing) {
            DrawText("How to Play:", 810, 400, 40, WHITE);
            DrawText("If the leaves are green, press the arrow keys in the direction they're pointing.\nIf the leaves are orange, press the arrow keys in the direction they're moving.", 520, 460, 20, WHITE);
            DrawText("Score the most points you can in 30 seconds. Good Luck!", 620, 505, 20, WHITE);
            DrawText("Press Enter to Continue", 810, 525, 20, LIGHTGRAY);
            if (score != 0) {
                DrawText(TextFormat("You got %d!", score), 850, 560, 30, WHITE);
                DrawText(TextFormat("Accuracy: %.1f%%", (100. * score) / attempts), 850, 595, 20, LIGHTGRAY);
            }
        } else {
            DrawText(TextFormat("Score: %i", score), 10, 10, 60, WHITE);
        }

        EndDrawing();
    }

    // UnloadTexture(greenleaf);
    // UnloadTexture(orangeleaf);
    CloseWindow();
    return 0;
}

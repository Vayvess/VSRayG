#include "lib.h"
#include "raylib.h"

const int WW = 800;
const int WH = 600;

note_t note;
int main(void) {
    InitWindow(WW, WH, "VSRayG");
    InitAudioDevice();
    SetTargetFPS(244);
    
    FILE *flevel = fopen("songs/out.vsrg", "r");
    struct stat sb;
    fstat(fileno(flevel), &sb);
    uint32_t bm_len = sb.st_size / sizeof(note_t);
    note_t *beatmap = malloc(sizeof(note_t) * bm_len);
    fread(beatmap, sizeof(note_t) * bm_len, 1, flevel);

    float dt;
    uint32_t x = 0;
    uint32_t elapsed = 0;
    Music level = LoadMusicStream("songs/audio.mp3");
    SetMusicVolume(level, 1.0f);
    PlayMusicStream(level);

    while (!WindowShouldClose()) {
        UpdateMusicStream(level);
        dt = GetFrameTime();
        elapsed += dt * 1000;
        BeginDrawing();
            ClearBackground(BLACK);

            if (IsKeyDown(KEY_S)) DrawRectangle(50, 536, 100, 32, WHITE);
            if (IsKeyDown(KEY_D)) DrawRectangle(150, 536, 100, 32, WHITE);
            if (IsKeyDown(KEY_F)) DrawRectangle(250, 536, 100, 32, WHITE);
            if (IsKeyDown(KEY_SPACE)) DrawRectangle(350, 536, 100, 32, WHITE);
            if (IsKeyDown(KEY_J)) DrawRectangle(450, 536, 100, 32, WHITE);
            if (IsKeyDown(KEY_K)) DrawRectangle(550, 536, 100, 32, WHITE);
            if (IsKeyDown(KEY_L)) DrawRectangle(650, 536, 100, 32, WHITE);

            int y = x;
            while (y < bm_len) {
                note_t *note = beatmap + y;
                if (elapsed > note->time) { x++; }
                else {
                    uint32_t delta = note->time - elapsed;
                    if (delta > 536) break;
                    DrawRectangle((note->lane - 1) * 100 + 50, 536 - delta, 100, 32, GREEN);
                }
                y++;
            }
            
            DrawLine(50, 0, 50, 600, WHITE);
            DrawLine(750, 0, 750, 600, WHITE);
            DrawLine(50, 536, 750, 536, WHITE);
            DrawLine(50, 568, 750, 568, WHITE);
        EndDrawing();
        if (x == bm_len) break;
    }

    free(beatmap);
    UnloadMusicStream(level);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

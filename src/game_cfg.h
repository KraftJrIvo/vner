#include <array>
#include <vector>

#include "raylib.h"

#define WIN_NOM "v n e r"

#define RAND_FLOAT static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) + 1.0f)
#define RAND_FLOAT_SIGNED (2.0f * RAND_FLOAT - 1.0f)
#define RAND_FLOAT_SIGNED_2D Vector2{RAND_FLOAT_SIGNED, RAND_FLOAT_SIGNED}

#define WINDOW_WIDTH   432
#define WINDOW_HEIGHT  864
#define MAX_WIDTH      512.f
#define N_TILES_WIDTH    16
#define TILE_SIZE      9.0f
#ifdef PLATFORM_ANDROID
    #define TILE_RADIUS    std::min(GetScreenWidth(), GetScreenHeight()) / (N_TILES_WIDTH * 2.0f)
#else
    #define TILE_RADIUS    std::min(std::min(GetScreenWidth(), GetScreenHeight()) / (N_TILES_WIDTH * 2.0f), MAX_WIDTH / (N_TILES_WIDTH * 2.0f))
#endif
#define TILE_PIXEL     (TILE_RADIUS * 2.0f) / TILE_SIZE
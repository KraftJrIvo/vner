#include <array>
#include <vector>

#include "raylib.h"

#define WIN_NOM "v n e r"

#define RAND_FLOAT static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) + 1.0f)
#define RAND_FLOAT_SIGNED (2.0f * RAND_FLOAT - 1.0f)
#define RAND_FLOAT_SIGNED_2D Vector2{RAND_FLOAT_SIGNED, RAND_FLOAT_SIGNED}

#define GAME_WIDTH_N 243
#define GAME_WIDTH_W 768
#define GAME_HEIGHT  432
#define GAME_SCALE_V ceil(GetScreenHeight() / float(GAME_HEIGHT))
#define GAME_SCALE_W std::min(ceil(GetScreenWidth() / float(GAME_WIDTH_W)), GAME_SCALE_V)
#define GAME_SCALE_N std::min(ceil(GetScreenWidth() / float(GAME_WIDTH_N)), GAME_SCALE_V)
#define IS_GAME_HOR (GetScreenWidth() > GetScreenHeight())
#define GAME_WIDTH  float(IS_GAME_HOR ? GAME_WIDTH_W : GAME_WIDTH_N)

#define GAME_SCALE_MAX float(int(GetMonitorHeight(GetCurrentMonitor())) / GAME_HEIGHT)
#define GAME_SCALE ((IS_GAME_HOR ? GAME_SCALE_W : GAME_SCALE_N))
#define GAME_TOP GAME_HEIGHT * (0.5f * (1.0f - (GetScreenHeight() / (GAME_SCALE * GAME_HEIGHT))))
#define GAME_LEFT   GAME_WIDTH * (0.5f * (1.0f - (GetScreenWidth() / (GAME_SCALE * GAME_WIDTH))))
#define GAME_BOTTOM GAME_HEIGHT * (1.0f - 0.5f * (1.0f - (GetScreenHeight() / (GAME_SCALE * GAME_HEIGHT))))
#define GAME_RIGHT   GAME_WIDTH * (1.0f - 0.5f * (1.0f - (GetScreenWidth() / (GAME_SCALE * GAME_WIDTH))))

#define WINDOW_WIDTH   GAME_SCALE_MAX * GAME_WIDTH_W
#define WINDOW_HEIGHT  GAME_SCALE_MAX * GAME_HEIGHT

#define MAX_BOOKS           16
#define MAX_CHAPTERS        16
#define MAX_BGS_PER_CHAP    16
#define MAX_SND_PER_CHAP    16
#define MAX_AMB_PER_CHAP    16
#define MAX_CHARS_PER_CHAP  16
#define MAX_SCENES_PER_CHAP 1
#define MAX_SCENE_TXT_LEN   128
#define MAX_CHAR_TXT_LEN    32
#define MAX_CHAP_TXT_LEN    64
#define MAX_BOOK_TXT_LEN    64
#define MAX_STATE_PER_CHAR  16
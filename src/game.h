#pragma once

#include "raylib.h"
#include "raymath.h"

#include "game_cfg.h"
#include "util/arena.h"
#include "util/drawable.h"
#include <cstddef>
#include <cstdint>
#include <vector>

#ifdef GAME_BASE_SHARED
#include "../../src/util/zpp_bits.h"
#endif

#ifdef GAME_BASE_SHARED    
#define DO_NOT_SERIALIZE friend zpp::bits::access; using serialize = zpp::bits::members<0>;        
#else
#define DO_NOT_SERIALIZE ;
#endif

struct State {
    Drawable drawable;
};

struct Character {
    std::array<char, MAX_CHAR_TXT_LEN> name;
    Color color;
    Arena<MAX_STATE_PER_CHAR, State> states;
};

struct Scene {
    size_t ambId;
    size_t bgId;
    size_t charId;
    std::array<char, MAX_SCENE_TXT_LEN> txt;
};

struct Chapter {
    std::array<char, MAX_CHAP_TXT_LEN> name;
    Arena<MAX_SCENES_PER_CHAP, Scene> scenes;
};

struct Book {
    std::array<char, MAX_BOOK_TXT_LEN> name;
    Arena<MAX_CHAPTERS, Chapter> chapters;
};

struct GameAssets {
    Music music;
    Shader postProcFragShader;
    Font font;
    Arena<MAX_AMB_PER_CHAP, Music> ambs;
    Arena<MAX_BGS_PER_CHAP, Drawable> bgs;
    Arena<MAX_SND_PER_CHAP, Sound> sounds;
    Arena<MAX_CHARS_PER_CHAP, Character> chars;
};

struct GameState {
    unsigned int seed;
    double time;
    double gameStartTime;

    Arena<MAX_BOOKS, Book> books;
    int curBookId = -1;
    int curChapId = -1;
    int curSceneId = -1;
    Vector2 spritePos;
    Vector2 spriteVel;
    Vector2 spriteSz;
    
    struct UserData {
        DO_NOT_SERIALIZE
        bool operator==(const UserData&) const = default;
    } usr;
    struct Temp {
        DO_NOT_SERIALIZE
        RenderTexture2D renderTexNative;
        RenderTexture2D renderTexFinal;
        bool timeOffsetSet = false;
        double timeOffset;
        float shTime;
    } tmp;
    struct AssetsPtr {
        DO_NOT_SERIALIZE
        const GameAssets* p;
    } ga;
};


#ifndef GAME_BASE_SHARED
extern "C" {
    void reset(GameState& gs);
    void init(GameAssets& ga, GameState& gs);
    void setState(GameState& gs, const GameState& ngs);
    void updateAndDraw(GameState& gs);
}
#endif

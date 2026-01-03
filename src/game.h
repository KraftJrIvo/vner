#pragma once

#include "raylib.h"
#include "raymath.h"

#include "game_cfg.h"

#ifdef GAME_BASE_DLL
#include "../../src/util/zpp_bits.h"
#endif

#ifdef GAME_BASE_DLL    
#define DO_NOT_SERIALIZE friend zpp::bits::access; using serialize = zpp::bits::members<0>;        
#else
#define DO_NOT_SERIALIZE ;
#endif

struct GameAssets {
    Music music;
    Shader postProcFragShader;
    Font font;
};

struct GameState {
    unsigned int seed;
    double time;
    double gameStartTime;

    //
    
    struct UserData {
        DO_NOT_SERIALIZE
        bool operator==(const UserData&) const = default;
    } usr;
    struct Temp {
        DO_NOT_SERIALIZE
        RenderTexture2D renderTex;
        bool timeOffsetSet = false;
        double timeOffset;
        float shTime;
    } tmp;
    struct AssetsPtr {
        DO_NOT_SERIALIZE
        const GameAssets* p;
    } ga;
};


#ifndef GAME_BASE_DLL
extern "C" {
    void init(GameAssets& ga, GameState& gs);
    void setState(GameState& gs, const GameState& ngs);
    void updateAndDraw(GameState& gs);
}
#endif

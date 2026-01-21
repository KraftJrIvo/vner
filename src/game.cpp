#include <string>

#include "game_basic.h"
#include "raylib.h"
#include "rlgl.h"

#include "util/tinyjson.hpp"
#include "util/vec_ops.h"

//tiny::TinyJson json;
//json.ReadJson(readFile("res/strings.json"));

#include "resources.h"
#include "resource_tree.h"

void dump_tree(int node, int depth) {
    const ResourceNode* n = &g_resource_nodes[node];
    // ... use n->name, n->path, n->is_dir, n->data, n->len ...
    std::cout << "";
    for (int child = n->first_child; child != -1; child = g_resource_nodes[child].next_sibling) {
        dump_tree(child, depth + 1);
    }
}

void _loadAssets(GameAssets& ga, GameState& gs) 
{
    //ga.sprite = LoadTextureFromImage(LoadImageFromMemory(".png", res_sprite_png, res_sprite_png_len));
    ga.music = LoadMusicStreamFromMemory(".ogg", res_music_ogg, res_music_ogg_len);
    //ga.sound = LoadSoundFromWave(LoadWaveFromMemory(".ogg", res_sound_ogg, res_sound_ogg_len));
    ga.postProcFragShader = LoadShaderFromMemory(NULL, (const char*)prepShader((unsigned char*)res_post_proc_fs).c_str());
    
    const char8_t allChars[228] = u8" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    int c; auto cdpts = LoadCodepoints((const char*)allChars, &c);
    ga.font = LoadFontFromMemory(".otf", res_font_otf, res_font_otf_len, 39, cdpts, c);

    dump_tree(g_resource_root_index, 0);
}

void _reset(GameState& gs) {
    gs.spritePos = Vector2{GAME_WIDTH, GAME_HEIGHT} * 0.5f;
    gs.spriteVel = RAND_FLOAT_SIGNED_2D;
    gs.spriteSz = Vector2{100.0f, 100.0f};
}

void updateMusic(GameState& gs) {
    //if (gs.usr.musEnabled) {
    //    UpdateMusicStream(gs.ga.p->music);
    //    auto musicLen = GetMusicTimeLength(gs.ga.p->music);
    //    auto musicTimePlayed = GetMusicTimePlayed(gs.ga.p->music);
    //}
}

void _updateAndDraw(GameState& gs) {
    auto delta = GetFrameTime();
    if (delta < 0.1f) {
        gs.spritePos += gs.spriteVel * 100.f * GetFrameTime();
        if (gs.spritePos.x - gs.spriteSz.x * 0.5f < 0 || gs.spritePos.x + gs.spriteSz.x * 0.5f > GAME_WIDTH) {
            gs.spriteVel.x *= -1.0f;
        }
        if (gs.spritePos.y - gs.spriteSz.y * 0.5f < 0 || gs.spritePos.y + gs.spriteSz.y * 0.5f > GAME_HEIGHT) {
            gs.spriteVel.y *= -1.0f;
        }
    }

    updateMusic(gs);
    
    ClearBackground(BLACK);
    DrawRectangleV(gs.spritePos - gs.spriteSz * 0.5f, gs.spriteSz, RED);
}

void _drawUI(GameState& gs) {
    DrawRectangleLines(0, 0, GAME_WIDTH, GAME_HEIGHT, GREEN);
    DrawCircleV({GAME_LEFT, GAME_HEIGHT * 0.5f}, 10, RED);
    DrawCircleV({GAME_RIGHT, GAME_HEIGHT * 0.5f}, 10, GREEN);
    DrawCircleV({GAME_WIDTH * 0.5f, GAME_BOTTOM}, 10, BLUE);
    DrawCircleV({GAME_WIDTH * 0.5f, GAME_TOP}, 10, WHITE);
}
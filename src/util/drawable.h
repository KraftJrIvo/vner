#include <raylib.h>
#include <string>

#include <string_view>
#include <cctype>
#include <optional>

inline std::optional<int> extractLastDecimalInt(std::string_view s) {
    int end = static_cast<int>(s.size()) - 1;
    while (end >= 0 && !std::isdigit(static_cast<unsigned char>(s[end])))
        --end;
    if (end < 0) 
        return std::nullopt;
    int start = end;
    while (start >= 0 && std::isdigit(static_cast<unsigned char>(s[start])))
        --start;
    int value = 0;
    for (int i = start + 1; i <= end; ++i)
        value = value * 10 + (s[i] - '0');
    return value;
}

class Drawable {
public:
    Texture2D tex;
    float fps;
    int nFrames;
    float frameW;

    Drawable() = default;

    Drawable(std::string texPath, float fps = 10.0f) :
        fps(fps)
    {
        tex = LoadTexture(texPath.c_str());
        if (tex.width % tex.height >= 2) {
            nFrames = tex.width / tex.height;
            frameW = tex.width / nFrames;
        } else {
            nFrames = 1;
            frameW = tex.width;
        }
        auto namefps = extractLastDecimalInt(texPath);
        if (namefps.has_value())
            this->fps = static_cast<float>(namefps.value());
    }

    void draw(Vector2 botcen) {
        auto frameIdx = (int)(GetTime() * fps) % nFrames;
        DrawTexturePro(tex, 
            {frameIdx * frameW, 0, (float)tex.width, (float)tex.height}, 
            {botcen.x - (float)tex.width/2, botcen.y - (float)tex.height/2, (float)tex.width, (float)tex.height}, 
            {0,0}, 0.0f, WHITE);
    }
};
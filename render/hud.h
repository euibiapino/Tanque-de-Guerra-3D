#pragma once

class HUD {
public:
    static void draw(int largura, int altura, float hp, float hpMax,
                     float cooldown, float cooldownMax, bool morto);
private:
    static void drawText(float x, float y, const char* texto);
    static void drawQuad(float x, float y, float w, float h);
};

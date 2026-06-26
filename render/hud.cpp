#include "hud.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdio>
#include <algorithm>

void HUD::drawQuad(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
    glVertex2f(x,     y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x,     y + h);
    glEnd();
}

void HUD::drawText(float x, float y, const char* texto) {
    glRasterPos2f(x, y);
    for (const char* c = texto; *c; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void HUD::draw(int largura, int altura, float hp, float hpMax,
               float cooldown, float cooldownMax, bool morto) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, largura, 0, altura, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // ---- Barra de vida ----
    const float barX = 20, barY = altura - 45;
    const float barW = 200, barH = 22;

    glColor4f(0.1f, 0.1f, 0.1f, 0.7f);
    drawQuad(barX - 2, barY - 2, barW + 4, barH + 4);

    float ratio = std::max(0.0f, hp / hpMax);
    glColor3f(1.0f - ratio, ratio * 0.9f, 0.0f);
    drawQuad(barX, barY, barW * ratio, barH);

    glColor3f(1, 1, 1);
    char buf[32];
    snprintf(buf, sizeof(buf), "HP  %d / %d", (int)hp, (int)hpMax);
    drawText(barX + 6, barY + 5, buf);

    // ---- Barra de recarga do tiro ----
    const float cdX = 20, cdY = 20;
    const float cdW = 120, cdH = 14;

    float prontidao = 1.0f - std::min(1.0f, cooldown / cooldownMax);

    glColor3f(0.1f, 0.1f, 0.1f);
    drawQuad(cdX - 2, cdY - 2, cdW + 4, cdH + 4);

    glColor3f(0.15f, 0.75f, 1.0f);
    drawQuad(cdX, cdY, cdW * prontidao, cdH);

    glColor3f(1, 1, 1);
    if (prontidao >= 1.0f)
        drawText(cdX + 4, cdY - 16, "PRONTO");
    else
        drawText(cdX + 4, cdY - 16, "RECARREGANDO...");

    // ---- Crosshair ----
    float cx = largura / 2.0f, cy = altura / 2.0f;
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(cx - 14, cy); glVertex2f(cx - 4, cy);
    glVertex2f(cx +  4, cy); glVertex2f(cx + 14, cy);
    glVertex2f(cx, cy - 14); glVertex2f(cx, cy - 4);
    glVertex2f(cx, cy +  4); glVertex2f(cx, cy + 14);
    glEnd();
    glLineWidth(1.0f);

    // ---- Game Over ----
    if (morto) {
        glColor3f(1.0f, 0.0f, 0.0f);
        drawText(largura / 2.0f - 70, altura / 2.0f + 10, "GAME  OVER");
        glColor3f(0.9f, 0.9f, 0.9f);
        drawText(largura / 2.0f - 90, altura / 2.0f - 14, "Pressione R para reiniciar");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

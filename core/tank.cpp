#include "tank.h"
#include "input.h"
#include "projectile.h"
#include "../render/textures.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <algorithm>

float Tank::anguloTanque        = 0.0f;
float Tank::posicaoTanqueX      = 0.0f;
float Tank::posicaoTanqueZ      = 0.0f;
float Tank::posicaoTanqueY      = 0.0f;
float Tank::deslocamentoEsteira = 0.0f;
float Tank::hp                  = 5.0f;
float Tank::cooldownTiro        = 0.0f;

const float Tank::HP_MAX           = 5.0f;
const float Tank::COOLDOWN_TIRO_MAX = 0.5f;

static const float VELOCIDADE   = 8.0f;
static const float VEL_ROTACAO  = 90.0f;
static const float LIMITE_MAPA  = 90.0f;

void Tank::updatePosition(float dt)
{
    if (hp <= 0.0f) return;

    float radiano = anguloTanque * M_PI / 180.0f;
    float dx = VELOCIDADE * sin(radiano) * dt;
    float dz = VELOCIDADE * cos(radiano) * dt;

    if (Input::teclaA) anguloTanque += VEL_ROTACAO * dt;
    if (Input::teclaD) anguloTanque -= VEL_ROTACAO * dt;

    if (Input::teclaW) {
        posicaoTanqueX += dx;
        posicaoTanqueZ += dz;
        deslocamentoEsteira += dt * 3.0f;
    }
    if (Input::teclaS) {
        posicaoTanqueX -= dx;
        posicaoTanqueZ -= dz;
        deslocamentoEsteira -= dt * 3.0f;
    }

    posicaoTanqueX = std::max(-LIMITE_MAPA, std::min(LIMITE_MAPA, posicaoTanqueX));
    posicaoTanqueZ = std::max(-LIMITE_MAPA, std::min(LIMITE_MAPA, posicaoTanqueZ));

    if (cooldownTiro > 0.0f) cooldownTiro -= dt;
}

void Tank::atirar() {
    if (cooldownTiro > 0.0f || hp <= 0.0f) return;

    float anguloTotal = (anguloTanque + Input::anguloTorreta) * (float)M_PI / 180.0f;
    float dirX = sinf(anguloTotal);
    float dirZ = cosf(anguloTotal);

    ProjectileSystem::atirar(
        posicaoTanqueX + dirX * 9.0f,
        posicaoTanqueZ + dirZ * 9.0f,
        dirX, dirZ, true);

    cooldownTiro = COOLDOWN_TIRO_MAX;
}

void Tank::receberDano(float dano) {
    hp -= dano;
    if (hp < 0.0f) hp = 0.0f;
}

void Tank::reiniciar() {
    posicaoTanqueX      = 0.0f;
    posicaoTanqueZ      = 0.0f;
    anguloTanque        = 0.0f;
    deslocamentoEsteira = 0.0f;
    hp                  = HP_MAX;
    cooldownTiro        = 0.0f;
    Input::anguloTorreta = 0.0f;
}

void Tank::desenharCorpo(float x, float y, float z)
{
    glBindTexture(GL_TEXTURE_2D, obterTextura(TEXTURA_CORPO));
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(1.0, 1.0, 1.0);
    glScalef(2.9, 2.4, 3.9);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -0.5, -1.25);
    glTexCoord2f(1.0, 0.0); glVertex3f( 1.0, -0.5, -1.25);
    glTexCoord2f(1.0, 1.0); glVertex3f( 1.0,  0.5, -1.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0,  0.5, -1.25);

    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -0.5,  1.25);
    glTexCoord2f(1.0, 0.0); glVertex3f( 1.0, -0.5,  1.25);
    glTexCoord2f(1.0, 1.0); glVertex3f( 1.0,  0.5,  1.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0,  0.5,  1.25);

    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -0.5, -1.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -0.5,  1.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0,  0.5,  1.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0,  0.5, -1.25);

    glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -0.5, -1.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -0.5,  1.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0,  0.5,  1.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0,  0.5, -1.25);

    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 0.5, -1.25);
    glTexCoord2f(1.0, 0.0); glVertex3f( 1.0, 0.5, -1.25);
    glTexCoord2f(1.0, 1.0); glVertex3f( 1.0, 0.5,  1.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 0.5,  1.25);

    glEnd();
    glPopMatrix();
}

void Tank::desenharEsteira(float x, float y, float z)
{
    glBindTexture(GL_TEXTURE_2D, obterTextura(TEXTURA_ESTEIRA));

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(0.0f, deslocamentoEsteira, 0.0f);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1.9, 3, 11);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5,  0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f( 0.5, -0.5,  0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f( 0.5,  0.5,  0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5,  0.5,  0.5);

    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f( 0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f( 0.5,  0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5,  0.5, -0.5);

    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5,  0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(-0.5,  0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5,  0.5,  0.5);

    glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5,  0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5,  0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.5,  0.5,  0.5);

    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5,  0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f( 0.5, 0.5,  0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f( 0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);

    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5,  0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f( 0.5, -0.5,  0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f( 0.5, -0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);

    glEnd();
    glPopMatrix();

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void Tank::desenharTorreta(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(Input::anguloTorreta, 0.0, 1.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, obterTextura(TEXTURA_TORRETA));
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(1.9, 14, 14);

    glBindTexture(GL_TEXTURE_2D, obterTextura(TEXTURA_CANO));
    glPushMatrix();
    glTranslatef(0.0, 0.0, 5.0);
    glScalef(0.4, 0.4, 8.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

void Tank::draw()
{
    desenharCorpo(0, 1.2f, 0);
    desenharTorreta(0, 3.0f, 0);
    desenharEsteira( 3.7f, 1.0f, 0.3f);
    desenharEsteira(-3.7f, 1.0f, 0.3f);
}

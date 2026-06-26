#include "enemy.h"
#include "projectile.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <cmath>

const float Enemy::HP_MAX          = 3.0f;
const float Enemy::RANGE_DETECCAO  = 38.0f;
const float Enemy::INTERVALO_TIRO  = 2.5f;

Enemy::Enemy(float startX, float startZ)
    : x(startX), z(startZ), angulo(0.0f), anguloTorreta(0.0f),
      hp(HP_MAX), cooldownTiro(INTERVALO_TIRO * 0.5f), ativo(true) {}

void Enemy::update(float dt, float playerX, float playerZ) {
    if (!ativo) return;

    float dX = playerX - x;
    float dZ = playerZ - z;
    float distancia = sqrtf(dX * dX + dZ * dZ);

    if (distancia < RANGE_DETECCAO) {
        float alvoAngulo = atan2f(dX, dZ) * 180.0f / (float)M_PI;

        // Suaviza rotação da torreta em direção ao jogador
        float diff = alvoAngulo - anguloTorreta;
        while (diff >  180.0f) diff -= 360.0f;
        while (diff < -180.0f) diff += 360.0f;
        anguloTorreta += diff * 2.5f * dt;

        cooldownTiro -= dt;
        if (cooldownTiro <= 0.0f) {
            float rad  = anguloTorreta * (float)M_PI / 180.0f;
            float dirX = sinf(rad);
            float dirZ = cosf(rad);
            ProjectileSystem::atirar(x + dirX * 7.0f, z + dirZ * 7.0f, dirX, dirZ, false);
            cooldownTiro = INTERVALO_TIRO;
        }
    }
}

void Enemy::receberDano(float dano) {
    hp -= dano;
    if (hp <= 0.0f) ativo = false;
}

void Enemy::draw() const {
    if (!ativo) return;

    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glRotatef(angulo, 0.0f, 1.0f, 0.0f);

    // Corpo
    glColor3f(0.55f, 0.08f, 0.08f);
    glPushMatrix();
    glTranslatef(0, 1.2f, 0);
    glScalef(2.9f, 1.2f, 3.9f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Esteiras
    glColor3f(0.15f, 0.15f, 0.15f);
    for (float lado : {1.85f, -1.85f}) {
        glPushMatrix();
        glTranslatef(lado, 0.5f, 0.3f);
        glScalef(0.5f, 1.0f, 4.2f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // Torreta (rotaciona em world-space, cancela rotação do body)
    glPushMatrix();
    glTranslatef(0, 3.0f, 0);
    glRotatef(-angulo, 0.0f, 1.0f, 0.0f);    // cancela body
    glRotatef(anguloTorreta, 0.0f, 1.0f, 0.0f); // aplica world-space

    glColor3f(0.65f, 0.1f, 0.1f);
    glutSolidSphere(1.7f, 12, 12);

    // Cano
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0, 0, 4.5f);
    glScalef(0.35f, 0.35f, 7.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix(); // torreta
    glPopMatrix(); // body
    glEnable(GL_TEXTURE_2D);
}

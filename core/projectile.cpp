#include "projectile.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <algorithm>

namespace ProjectileSystem {

std::vector<Projectile> projeteis;

static const float VELOCIDADE = 30.0f;
static const float VIDA_MAX   = 3.0f;

void atirar(float x, float z, float dirX, float dirZ, bool doJogador) {
    projeteis.push_back({x, z, dirX, dirZ, VIDA_MAX, doJogador});
}

void update(float dt) {
    for (auto& p : projeteis) {
        p.x += p.dirX * VELOCIDADE * dt;
        p.z += p.dirZ * VELOCIDADE * dt;
        p.vidaRestante -= dt;
    }
    projeteis.erase(
        std::remove_if(projeteis.begin(), projeteis.end(),
            [](const Projectile& p) {
                return p.vidaRestante <= 0.0f ||
                       p.x < -50.0f || p.x > 50.0f ||
                       p.z < -50.0f || p.z > 50.0f;
            }),
        projeteis.end());
}

void draw() {
    glDisable(GL_TEXTURE_2D);
    for (const auto& p : projeteis) {
        glPushMatrix();
        glTranslatef(p.x, 1.8f, p.z);
        if (p.doJogador) glColor3f(1.0f, 0.95f, 0.0f);
        else             glColor3f(1.0f, 0.3f,  0.0f);
        glutSolidSphere(0.35f, 8, 8);
        glPopMatrix();
    }
    glEnable(GL_TEXTURE_2D);
}

} // namespace ProjectileSystem

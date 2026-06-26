#include "obstacles.h"
#include <GL/glut.h>
#include <GL/gl.h>

namespace Obstacles {

std::vector<Obstaculo> lista;

void inicializar() {
    lista.clear();

    // Árvores: (x, z, escala)
    const float arvores[][3] = {
        {-18, -12, 1.1f}, { 22,  16, 1.3f}, {-28,  22, 0.9f},
        { 12, -32, 1.2f}, { 48,  48, 1.0f}, {-48,  12, 1.4f},
        { 32, -50, 1.1f}, {-14,  42, 1.0f}, { 18,  36, 1.2f},
        {-42, -18, 0.8f}, { 55, -55, 1.3f}, {-55,  55, 1.0f},
        { 60,  20, 1.1f}, {-60, -45, 0.9f}, { 45, -80, 1.2f},
        {-70,  30, 1.0f}, { 70, -30, 1.3f}, {-15,  70, 1.1f},
        { 25, -70, 0.9f}, {-50,  65, 1.0f},
    };
    for (auto& a : arvores)
        lista.push_back({TipoObstaculo::ARVORE, a[0], a[1], a[2], 2.2f * a[2]});

    // Pedras: (x, z, escala)
    const float pedras[][3] = {
        { -8,  22, 1.4f}, { 28, -16, 1.6f}, {-22, -45, 1.2f},
        { 48,  28, 1.5f}, {-42, -42, 1.3f}, { 38,  48, 1.1f},
        {-32,  35, 1.4f}, { 65, -10, 1.2f}, {-65,  20, 1.6f},
        { 15, -60, 1.3f}, {-55, -65, 1.1f}, { 80,  45, 1.4f},
    };
    for (auto& p : pedras)
        lista.push_back({TipoObstaculo::PEDRA, p[0], p[1], p[2], 1.8f * p[2]});
}

static void desenharArvore(const Obstaculo& o) {
    // Tronco
    glColor3f(0.38f, 0.22f, 0.09f);
    glPushMatrix();
    glTranslatef(o.x, 0.0f, o.z);
    glScalef(0.35f, 3.2f * o.escala, 0.35f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Copa
    glColor3f(0.12f, 0.48f, 0.12f);
    glPushMatrix();
    glTranslatef(o.x, 3.2f * o.escala, o.z);
    glutSolidSphere(1.9f * o.escala, 10, 8);
    glPopMatrix();

    // Segunda camada de copa (levemente acima)
    glColor3f(0.09f, 0.38f, 0.09f);
    glPushMatrix();
    glTranslatef(o.x, 4.5f * o.escala, o.z);
    glutSolidSphere(1.2f * o.escala, 8, 6);
    glPopMatrix();
}

static void desenharPedra(const Obstaculo& o) {
    glColor3f(0.52f, 0.50f, 0.46f);
    glPushMatrix();
    glTranslatef(o.x, 0.5f * o.escala, o.z);
    glScalef(o.escala * 1.6f, o.escala * 0.85f, o.escala * 1.2f);
    glutSolidSphere(1.0f, 8, 6);
    glPopMatrix();

    // Segunda pedra menor ao lado para variar
    glColor3f(0.44f, 0.42f, 0.38f);
    glPushMatrix();
    glTranslatef(o.x + o.escala * 1.2f, 0.3f * o.escala, o.z + o.escala * 0.5f);
    glScalef(o.escala * 0.8f, o.escala * 0.55f, o.escala * 0.7f);
    glutSolidSphere(1.0f, 7, 5);
    glPopMatrix();
}

void draw() {
    glDisable(GL_TEXTURE_2D);
    for (const auto& o : lista) {
        if (o.tipo == TipoObstaculo::ARVORE) desenharArvore(o);
        else                                 desenharPedra(o);
    }
    glEnable(GL_TEXTURE_2D);
}

} // namespace Obstacles

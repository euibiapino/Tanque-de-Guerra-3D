#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include <GL/glu.h>
#include "core/camera.h"
#include "core/input.h"
#include "core/tank.h"
#include "core/terrain.h"
#include "core/projectile.h"
#include "core/enemy.h"
#include "core/obstacles.h"
#include "render/textures.h"
#include "render/lighting.h"
#include "render/hud.h"

static int larguraJanela = 800;
static int alturaJanela  = 600;
static int ultimoTempo   = 0;

static std::vector<Enemy> inimigos;

// ---- Céu gradiente ----
static void desenharCeu() {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_QUADS);
    glColor3f(0.12f, 0.38f, 0.80f);   // azul profundo (topo)
    glVertex2f(-1,  1);
    glVertex2f( 1,  1);
    glColor3f(0.65f, 0.82f, 0.96f);   // azul claro (horizonte)
    glVertex2f( 1, -1);
    glVertex2f(-1, -1);
    glEnd();

    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// ---- Sombra elíptica no chão ----
static void desenharSombra(float x, float z, float rx, float rz) {
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(0.05f, 0.08f, 0.05f);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0f, -1.0f);

    glPushMatrix();
    glTranslatef(x, -0.48f, z);
    glScalef(rx, 0.01f, rz);
    glutSolidSphere(1.0f, 14, 4);
    glPopMatrix();

    glDisable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

// ---- Colisões ----
static void verificarColisoes() {
    for (auto& p : ProjectileSystem::projeteis) {
        if (p.vidaRestante <= 0.0f) continue;

        // Projétil do jogador vs inimigos
        if (p.doJogador) {
            for (auto& e : inimigos) {
                if (!e.ativo) continue;
                float dx = p.x - e.x, dz = p.z - e.z;
                if (dx * dx + dz * dz < 10.0f) {
                    e.receberDano(1.0f);
                    p.vidaRestante = 0.0f;
                }
            }
        } else {
            // Projétil inimigo vs jogador
            float dx = p.x - Tank::posicaoTanqueX;
            float dz = p.z - Tank::posicaoTanqueZ;
            if (dx * dx + dz * dz < 16.0f) {
                Tank::receberDano(1.0f);
                p.vidaRestante = 0.0f;
            }
        }

        // Qualquer projétil vs obstáculos
        for (const auto& o : Obstacles::lista) {
            float dx = p.x - o.x, dz = p.z - o.z;
            if (dx * dx + dz * dz < o.raioColisao * o.raioColisao) {
                p.vidaRestante = 0.0f;
            }
        }
    }
}

static void colisaoTankObstaculos() {
    const float raioTank = 3.2f;
    for (const auto& o : Obstacles::lista) {
        float dx = Tank::posicaoTanqueX - o.x;
        float dz = Tank::posicaoTanqueZ - o.z;
        float dist2 = dx * dx + dz * dz;
        float minDist = raioTank + o.raioColisao;
        if (dist2 < minDist * minDist && dist2 > 0.001f) {
            float dist = sqrtf(dist2);
            Tank::posicaoTanqueX = o.x + (dx / dist) * minDist;
            Tank::posicaoTanqueZ = o.z + (dz / dist) * minDist;
        }
    }
}

// ---- Enemies ----
static void criarInimigos() {
    inimigos.clear();
    inimigos.emplace_back(-35.0f, -35.0f);
    inimigos.emplace_back( 40.0f, -25.0f);
    inimigos.emplace_back(  0.0f,  45.0f);
    inimigos.emplace_back(-60.0f,  50.0f);
    inimigos.emplace_back( 65.0f,  60.0f);
}

// ---- Render ----
void exibir() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    desenharCeu();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspecto = (float)larguraJanela / (float)alturaJanela;
    gluPerspective(45.0, aspecto, 0.1, 300.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Camera::setupView(Tank::posicaoTanqueX, Tank::posicaoTanqueZ, Tank::posicaoTanqueY,
                      Input::anguloTorreta, Tank::anguloTanque);

    // Sombras (antes do terreno para usar polygon offset)
    desenharSombra(Tank::posicaoTanqueX, Tank::posicaoTanqueZ, 3.5f, 4.5f);
    for (const auto& e : inimigos)
        if (e.ativo) desenharSombra(e.x, e.z, 3.0f, 4.0f);

    Terrain::draw();
    Obstacles::draw();

    glPushMatrix();
    glTranslatef(Tank::posicaoTanqueX, 0.0f, Tank::posicaoTanqueZ);
    glRotatef(Tank::anguloTanque, 0.0f, 1.0f, 0.0f);
    Tank::draw();
    glPopMatrix();

    for (const auto& e : inimigos)
        e.draw();

    ProjectileSystem::draw();

    bool morto = (Tank::hp <= 0.0f);
    HUD::draw(larguraJanela, alturaJanela, Tank::hp, Tank::HP_MAX,
              Tank::cooldownTiro, Tank::COOLDOWN_TIRO_MAX, morto);

    glutSwapBuffers();
}

void redimensionar(int largura, int altura) {
    if (altura == 0) altura = 1;
    larguraJanela = largura;
    alturaJanela  = altura;
    glViewport(0, 0, largura, altura);
}

void atualizar(int) {
    int tempoAtual = glutGet(GLUT_ELAPSED_TIME);
    float dt = (tempoAtual - ultimoTempo) / 1000.0f;
    ultimoTempo = tempoAtual;
    if (dt > 0.05f) dt = 0.05f;

    if (Input::teclaR) {
        Tank::reiniciar();
        criarInimigos();
        ProjectileSystem::projeteis.clear();
        Input::teclaR = false;
    }

    if (Input::teclaEspaco)
        Tank::atirar();

    Tank::updatePosition(dt);
    colisaoTankObstaculos();

    ProjectileSystem::update(dt);

    for (auto& e : inimigos)
        e.update(dt, Tank::posicaoTanqueX, Tank::posicaoTanqueZ);

    verificarColisoes();

    glutPostRedisplay();
    glutTimerFunc(16, atualizar, 0);
}

static void configurarNevoa() {
    GLfloat corNevoa[] = {0.65f, 0.82f, 0.96f, 1.0f};
    glFogfv(GL_FOG_COLOR, corNevoa);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START,  80.0f);
    glFogf(GL_FOG_END,   200.0f);
    glEnable(GL_FOG);
}

void inicializar() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    if (!carregarTextura()) {
        std::cerr << "Falha ao carregar texturas" << std::endl;
        exit(1);
    }

    configurarIluminacao();
    configurarNevoa();
    glClearColor(0.65f, 0.82f, 0.96f, 1.0f);  // cor da névoa = horizonte

    Obstacles::inicializar();
    criarInimigos();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(larguraJanela, alturaJanela);
    glutCreateWindow("Tanque de Guerra 3D");

    inicializar();
    ultimoTempo = glutGet(GLUT_ELAPSED_TIME);

    glutDisplayFunc(exibir);
    glutReshapeFunc(redimensionar);
    glutKeyboardFunc(Input::handleKeyboard);
    glutKeyboardUpFunc(Input::handleKeyboardUp);
    glutSpecialFunc(Input::handleSpecialKeys);
    glutTimerFunc(16, atualizar, 0);

    glutMainLoop();
    return 0;
}

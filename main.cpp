#include <ostream>
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include "core/camera.h"
#include "core/input.h"
#include "core/tank.h"
#include "core/terrain.h"
#include "render/textures.h"
#include "render/lighting.h"

void exibir() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Camera::setupView(Tank::posicaoTanqueX, Tank::posicaoTanqueZ, Tank::posicaoTanqueY, Input::anguloTorreta);
    Tank::updatePosition();

    Terrain::draw();

    glPushMatrix();
    glTranslatef(Tank::posicaoTanqueX, 0.0, Tank::posicaoTanqueZ); 
    glRotatef(Tank::anguloTanque, 0.0, 1.0, 0.0);
    Tank::draw();
    glPopMatrix();

    glutSwapBuffers();
}

void inicializar() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    if(!carregarTextura()) {
        std::cerr << "Falha ao carregar texturas" << std::endl;
        exit(1);
    }

    configurarIluminacao();
    glClearColor(0.68f, 0.85f, 0.9f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tanque 3D");
    inicializar();
    glutDisplayFunc(exibir);
    glutKeyboardFunc(Input::handleKeyboard);
    glutKeyboardUpFunc(Input::handleKeyboardUp);
    glutSpecialFunc(Input::handleSpecialKeys);
    glutMainLoop();
    return 0;
}
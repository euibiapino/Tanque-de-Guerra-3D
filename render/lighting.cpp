#include <GL/glut.h>
#include "lighting.h"

void configurarIluminacao() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat luzAmbiente[] = { 0.8, 0.8, 0.8, 1.0 }; 
    GLfloat luzDifusa[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat luzSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat posicaoLuz[] = { 10.0, 10.0, 10.0, 1.0 }; 

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    GLfloat ambienteMaterial[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat difusoMaterial[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat especularMaterial[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat brilhoMaterial[] = { 80.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambienteMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difusoMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularMaterial);
    glMaterialfv(GL_FRONT, GL_SHININESS, brilhoMaterial);

    glShadeModel(GL_SMOOTH);
}

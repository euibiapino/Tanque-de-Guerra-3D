#include "input.h"
#include "camera.h"
#include <GL/glut.h>

bool Input::teclaW = false;
bool Input::teclaA = false;
bool Input::teclaS = false;
bool Input::teclaD = false;
float Input::anguloTorreta = 0.0;

void Input::handleKeyboard(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'w': case 'W': teclaW = true; break;
        case 's': case 'S': teclaS = true; break;
        case 'a': case 'A': teclaA = true; break;
        case 'd': case 'D': teclaD = true; break;
        case 'v': case 'V': Camera::toggleViewMode(); break;
    }
    glutPostRedisplay();
}

void Input::handleKeyboardUp(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'w': case 'W': teclaW = false; break;
        case 's': case 'S': teclaS = false; break;
        case 'a': case 'A': teclaA = false; break;
        case 'd': case 'D': teclaD = false; break;
    }
    glutPostRedisplay();
}

void Input::handleSpecialKeys(int tecla, int x, int y) {
    switch (tecla) {
        case GLUT_KEY_LEFT: anguloTorreta += 5.0; break;
        case GLUT_KEY_RIGHT: anguloTorreta -= 5.0; break;
    }
    glutPostRedisplay();
}
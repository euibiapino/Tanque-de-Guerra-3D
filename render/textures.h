#pragma once
#include <GL/glut.h>

enum textureType {
    TEXTURA_CORPO,
    TEXTURA_TORRETA,
    TEXTURA_CANO,
    TEXTURA_TERRENO,
    TEXTURA_ESTEIRA,
    NUM_TEXTURES
};

bool carregarTextura();

GLuint obterTextura(textureType tipo);

void liberarTextura();
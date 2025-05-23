#include "terrain.h"
#include "../render/textures.h"
#include <GL/glut.h>

void Terrain::draw() {
    glBindTexture(GL_TEXTURE_2D, obterTextura(TEXTURA_TERRENO)); 
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -0.5, -50.0);
    glTexCoord2f(50.0, 0.0); glVertex3f(50.0, -0.5, -50.0);
    glTexCoord2f(50.0, 50.0); glVertex3f(50.0, -0.5, 50.0);
    glTexCoord2f(0.0, 50.0); glVertex3f(-50.0, -0.5, 50.0);
    
    glEnd();
}
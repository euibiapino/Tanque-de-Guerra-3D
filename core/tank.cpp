#include "tank.h"
#include "input.h"
#include "../render/textures.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

float Tank::anguloTanque = 0.0;
float Tank::posicaoTanqueX = 0.0;
float Tank::posicaoTanqueZ = 0.0;
float Tank::posicaoTanqueY = 0.0;

void Tank::updatePosition()
{
    float velocidade = 0.3;
    float radiano = anguloTanque * M_PI / 180.0;
    float dx = velocidade * sin(radiano);
    float dz = velocidade * cos(radiano);

    if (Input::teclaA)
    {
        anguloTanque += 5.0;
    }
    if (Input::teclaD)
    {
        anguloTanque -= 5.0;
    }
    if (Input::teclaW)
    {
        posicaoTanqueX += dx;
        posicaoTanqueZ += dz;
    }
    if (Input::teclaS)
    {
        posicaoTanqueX -= dx;
        posicaoTanqueZ -= dz;
    }
}

void Tank::desenharCorpo(float x, float y, float z)
    {

        glBindTexture(GL_TEXTURE_2D, obterTextura(TEXTURA_CORPO));
        glPushMatrix();
        glTranslatef(x, y, z);
        glColor3f(1.0, 1.0, 1.0);
        glScalef(2.9, 2.4, 3.9);

        glBegin(GL_QUADS);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1.0, -0.5, -1.25);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0, -0.5, -1.25);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0, 0.5, -1.25);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0, 0.5, -1.25);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1.0, -0.5, 1.25);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0, -0.5, 1.25);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0, 0.5, 1.25);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0, 0.5, 1.25);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1.0, -0.5, -1.25);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-1.0, -0.5, 1.25);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-1.0, 0.5, 1.25);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0, 0.5, -1.25);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.0, -0.5, -1.25);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0, -0.5, 1.25);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0, 0.5, 1.25);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(1.0, 0.5, -1.25);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1.0, 0.5, -1.25);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0, 0.5, -1.25);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0, 0.5, 1.25);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0, 0.5, 1.25);
        glEnd();
        glPopMatrix();
    }

    void Tank::desenharEsteira(float x, float y, float z)
    {
        glBindTexture(GL_TEXTURE_2D, obterTextura(TEXTURA_ESTEIRA));
        glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(1.9, 3, 11);

        glBegin(GL_QUADS);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0.5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.5, -0.5, 0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.5, 0.5, 0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.5, 0.5, 0.5);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.5, -0.5, -0.5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.5, -0.5, -0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.5, 0.5, -0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.5, 0.5, -0.5);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0.5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-0.5, -0.5, -0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-0.5, 0.5, -0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.5, 0.5, 0.5);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.5, -0.5, 0.5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.5, -0.5, -0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.5, 0.5, -0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(0.5, 0.5, 0.5);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.5, 0.5, 0.5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.5, 0.5, 0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.5, 0.5, -0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.5, 0.5, -0.5);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0.5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.5, -0.5, 0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.5, -0.5, -0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.5, -0.5, -0.5);

        glEnd();
        glPopMatrix();
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
    desenharCorpo(0, 1.2, 0);
    desenharTorreta(0, 3, 0);
    desenharEsteira(3.7, 1, 0.3);
    desenharEsteira(-3.7, 1, 0.3);
}
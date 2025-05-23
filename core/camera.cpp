#include "camera.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

ModoVisao Camera::modoVisao = Tpessoa;
float Camera::cameraDirecao = 1.5;
float Camera::cameraOffsetX = 0;
float Camera::cameraOffsetZ = 10;
float Camera::cameraAltura = 5.0;

void Camera::setupView(float posicaoTanqueX, float posicaoTanqueZ, float posicaoTanqueY, float anguloTorreta) {
    float cameraDistancia = 35.0;
    float cameraDesloAltura = 5.0;

    float cameraPosX = posicaoTanqueX;
    float cameraPosY = (modoVisao == Ppessoa) ? cameraAltura : 20;
    float cameraPosZ = posicaoTanqueZ;
    
    float radianoTorreta = anguloTorreta * M_PI / 180.0;
    float cameraDirX = sin(radianoTorreta);
    float cameraDirZ = cos(radianoTorreta);

    if (modoVisao == Ppessoa) {
        gluLookAt(cameraPosX, cameraPosY, cameraPosZ,  
                cameraPosX + cameraDirX, cameraPosY, cameraPosZ + cameraDirZ,
                0.0, 1.0, 0.0);
    } else {
        gluLookAt(cameraPosX - cameraDirX * cameraDistancia, 
                cameraDesloAltura + 20, 
                cameraPosZ - cameraDirZ * cameraDistancia, 
                posicaoTanqueX, 
                posicaoTanqueY, 
                posicaoTanqueZ, 
                0.0, 1.0, 0.0);
    }
}

void Camera::toggleViewMode() {
    modoVisao = (modoVisao == Tpessoa) ? Ppessoa : Tpessoa;
}
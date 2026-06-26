#include "camera.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

ModoVisao Camera::modoVisao = Tpessoa;
float Camera::cameraDirecao = 1.5;
float Camera::cameraOffsetX = 0;
float Camera::cameraOffsetZ = 10;
float Camera::cameraAltura = 5.0;

void Camera::setupView(float posicaoTanqueX, float posicaoTanqueZ, float posicaoTanqueY, float anguloTorreta, float anguloTanque) {
    const float cameraDistancia = 35.0f;
    const float cameraDesloAltura = 25.0f;

    float radianoTorreta = anguloTorreta * M_PI / 180.0;
    float torretaDirX = sin(radianoTorreta);
    float torretaDirZ = cos(radianoTorreta);

    float radianoTanque = anguloTanque * M_PI / 180.0;
    float tanqueDirX = sin(radianoTanque);
    float tanqueDirZ = cos(radianoTanque);

    if (modoVisao == Ppessoa) {
        gluLookAt(posicaoTanqueX, cameraAltura, posicaoTanqueZ,
                  posicaoTanqueX + torretaDirX, cameraAltura, posicaoTanqueZ + torretaDirZ,
                  0.0, 1.0, 0.0);
    } else {
        gluLookAt(posicaoTanqueX - tanqueDirX * cameraDistancia,
                  cameraDesloAltura,
                  posicaoTanqueZ - tanqueDirZ * cameraDistancia,
                  posicaoTanqueX, posicaoTanqueY, posicaoTanqueZ,
                  0.0, 1.0, 0.0);
    }
}

void Camera::toggleViewMode() {
    modoVisao = (modoVisao == Tpessoa) ? Ppessoa : Tpessoa;
}
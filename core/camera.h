#pragma once

enum ModoVisao { Tpessoa, Ppessoa };

class Camera {
public:
    static ModoVisao modoVisao;
    static float cameraDirecao;
    static float cameraOffsetX;
    static float cameraOffsetZ;
    static float cameraAltura;

    static void setupView(float posicaoTanqueX, float posicaoTanqueZ, float posicaoTanqueY, float anguloTorreta);
    static void toggleViewMode();
};
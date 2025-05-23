#pragma once

class Tank {
public:
    static float anguloTanque;
    static float posicaoTanqueX;
    static float posicaoTanqueZ;
    static float posicaoTanqueY;

    static void updatePosition();
    static void draw();

private:
    static void desenharCorpo(float x, float y, float z);
    static void desenharTorreta(float x, float y, float z);
    static void desenharEsteira(float x, float y, float z);
};
#pragma once

class Tank {
public:
    static float anguloTanque;
    static float posicaoTanqueX;
    static float posicaoTanqueZ;
    static float posicaoTanqueY;
    static float deslocamentoEsteira;
    static float hp;
    static float cooldownTiro;

    static const float HP_MAX;
    static const float COOLDOWN_TIRO_MAX;

    static void updatePosition(float dt);
    static void atirar();
    static void receberDano(float dano);
    static void reiniciar();
    static void draw();

private:
    static void desenharCorpo(float x, float y, float z);
    static void desenharTorreta(float x, float y, float z);
    static void desenharEsteira(float x, float y, float z);
};
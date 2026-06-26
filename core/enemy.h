#pragma once
#include <vector>

class Enemy {
public:
    float x, z;
    float angulo;
    float anguloTorreta;
    float hp;
    float cooldownTiro;
    bool ativo;

    Enemy(float startX, float startZ);
    void update(float dt, float playerX, float playerZ);
    void draw() const;
    void receberDano(float dano);

    static const float HP_MAX;
    static const float RANGE_DETECCAO;
    static const float INTERVALO_TIRO;
};

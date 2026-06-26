#pragma once
#include <vector>

struct Projectile {
    float x, z;
    float dirX, dirZ;
    float vidaRestante;
    bool doJogador;
};

namespace ProjectileSystem {
    extern std::vector<Projectile> projeteis;
    void atirar(float x, float z, float dirX, float dirZ, bool doJogador);
    void update(float dt);
    void draw();
}

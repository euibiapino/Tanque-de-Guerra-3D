#pragma once
#include <vector>

enum class TipoObstaculo { ARVORE, PEDRA };

struct Obstaculo {
    TipoObstaculo tipo;
    float x, z;
    float escala;
    float raioColisao;
};

namespace Obstacles {
    extern std::vector<Obstaculo> lista;
    void inicializar();
    void draw();
}

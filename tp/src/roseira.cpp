//
// Created by david on 01/11/2025.
//

#include "../include/roseira.h"
#include "../include/celula.h"
#include "../include/jardim.h"
#include <cstdlib>
#include <algorithm> // Para std::max

Roseira::Roseira() : Planta(25, 25) {
}

bool Roseira::deveMorrer(Jardim* jardim, int lin, int col) {
    // 1. Água ou nutrientes internos = 0
    if (agua_interna <= 0 || nutrientes_interna <= 0) return true;

    // 2. Nutrientes internos ≥ 200
    if (nutrientes_interna >= 200) return true;

    // 3. Todas as 4 vizinhas têm planta
    int vizinhos_ocupados = 0;
    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
    for (auto& d : dirs) {
        int nl = lin + d[0], nc = col + d[1];
        if (jardim->posicaoValida(nl, nc) &&
            jardim->getCelula(nl, nc).getPlanta() != nullptr) {
            vizinhos_ocupados++;
        }
    }
    return (vizinhos_ocupados == 4);
}

bool Roseira::tentarMultiplicar(Jardim* jardim, int lin, int col) {
    if (nutrientes_interna <= 100) return false;

    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
    for (auto& d : dirs) {
        int nl = lin + d[0], nc = col + d[1];
        if (jardim->posicaoValida(nl, nc) &&
            jardim->getCelula(nl, nc).getPlanta() == nullptr) {

            Roseira* nova = new Roseira();
            // Metade da água
            nova->agua_interna = agua_interna / 2;
            // 25 nutrientes
            nova->nutrientes_interna = Settings::Roseira::nova_nutrientes;

            // Atualizar original
            // Metade restante
            agua_interna = agua_interna / 2;
            // Fica com 100
            nutrientes_interna = Settings::Roseira::original_nutrientes;

            jardim->getCelula(nl, nc).setPlanta(nova);
            return true;
        }
    }
    return false;
}

void Roseira::atualizar(Jardim* jardim, int lin, int col) {
    Celula& cel = jardim->getCelula(lin, col);

    // 1. Perde 4 água e 4 nutrientes
    agua_interna = std::max(0, agua_interna - Settings::Roseira::perda_agua);
    nutrientes_interna = std::max(0, nutrientes_interna - Settings::Roseira::perda_nutrientes);

    // 2. Absorve 5 água e 8 nutrientes do solo (se houver)
    int absorve_agua = std::min(Settings::Roseira::absorcao_agua, cel.getAgua());
    int absorve_nut = std::min(Settings::Roseira::absorcao_nutrientes, cel.getNutrientes());

    agua_interna += absorve_agua;
    nutrientes_interna += absorve_nut;
    cel.setAgua(cel.getAgua() - absorve_agua);
    cel.setNutrientes(cel.getNutrientes() - absorve_nut);

    // 3. Verificar morte
    if (deveMorrer(jardim, lin, col)) {
        // Deixa metade da água e nutrientes no solo
        cel.setAgua(cel.getAgua() + agua_interna / 2);
        cel.setNutrientes(cel.getNutrientes() + nutrientes_interna / 2);
        cel.removerPlanta();  // morre
        delete this;          // importante: liberação
        return;
    }

    // 4. Tentar multiplicar
    tentarMultiplicar(jardim, lin, col);

    // 5. Envelhecer
    envelhecer();
}
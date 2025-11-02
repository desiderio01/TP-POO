#include "../include/ferramentaz.h"
#include "../include/jardim.h"

FerramentaZ::FerramentaZ() : Ferramenta(3, 'z') {}  // 3 usos

void FerramentaZ::usar(Jardim* jardim, int lin, int col) {
    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
    for (auto& d : dirs) {
        int nl = lin + d[0], nc = col + d[1];
        if (jardim->posicaoValida(nl, nc)) {
            Celula& cel = jardim->getCelula(nl, nc);
            if (cel.getPlanta() != nullptr) {
                cel.removerPlanta();
            }
        }
    }
    reduzirUso();
}
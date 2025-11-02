#include "../include/tesourapoda.h"
#include "../include/jardim.h"
#include "../include/celula.h"
#include "../include/ervadaninha.h"

TesouraPoda::TesouraPoda() : Ferramenta(0, '<') {}  // 0 = infinito

void TesouraPoda::usar(Jardim* jardim, int lin, int col) {
    Celula& cel = jardim->getCelula(lin, col);
    Planta* p = cel.getPlanta();

    // Só corta erva daninha
    if (dynamic_cast<ErvaDaninha*>(p) != nullptr) {
        cel.removerPlanta();  // delete interno
    }
}
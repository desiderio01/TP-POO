#include "../include/jardineiro.h"
#include "../include/ferramenta.h"
#include "../include/jardim.h"

Jardineiro::Jardineiro(int lin, int col) : linha(lin), coluna(col) {}

Jardineiro::~Jardineiro() {
    for (auto f : ferramentas) {
        delete f;  // Libera memória
    }
}

void Jardineiro::mover(char direcao, int max_lin, int max_col) {
    if (direcao == 'n' && linha > 0) linha--;
    else if (direcao == 's' && linha < max_lin - 1) linha++;
    else if (direcao == 'o' && coluna > 0) coluna--;
    else if (direcao == 'e' && coluna < max_col - 1) coluna++;
}

void Jardineiro::adicionarFerramenta(Ferramenta* f) {
    ferramentas.push_back(f);
}

void Jardineiro::usarFerramenta(Jardim* jardim) {
    if (ferramentas.empty()) return;

    Ferramenta* f = ferramentas.back();  // Última = na mão
    if (!f->estaDesgastada()) {
        f->usar(jardim, linha, coluna);
    }
}

void Jardineiro::entrar(int lin, int col) {
    // Comando 'entra'
    // Se o jardineiro já estiver no jardim, o efeito é o de se teletransportar
    linha = lin;
    coluna = col;
}

bool Jardineiro::temFerramenta(const std::string& tipo) const {
    for (const auto& f : ferramentas) {
        if (f->getTipo() == tipo) return true;
    }
    return false;
}
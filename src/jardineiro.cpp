#include "../include/jardineiro.h"
#include "../include/ferramenta.h"
#include "../include/jardim.h"
#include <iostream>

// Construtor: Inicializa o array dinâmico
Jardineiro::Jardineiro(int lin, int col)
    : linha(lin), coluna(col), numFerramentas(0), capacidade(2) { // Começa com capacidade 2

    ferramentas = new Ferramenta*[capacidade];
}

// Destrutor: Liberta toda a memória
Jardineiro::~Jardineiro() {
    // 1. Apaga cada ferramenta individualmente (pois o Jardineiro é "dono")
    for (int i = 0; i < numFerramentas; i++) {
        delete ferramentas[i];
    }
    // 2. Apaga o array de ponteiros
    delete[] ferramentas;
}

// Helper privado para aumentar o array
void Jardineiro::redimensionar() {
    int novaCapacidade = capacidade * 2;
    Ferramenta** novoArray = new Ferramenta*[novaCapacidade];

    // Copia os ponteiros antigos para o novo array
    for (int i = 0; i < numFerramentas; i++) {
        novoArray[i] = ferramentas[i];
    }

    // Liberta o array antigo
    delete[] ferramentas;

    // Atualiza os membros
    ferramentas = novoArray;
    capacidade = novaCapacidade;
}

// Adiciona uma ferramenta, redimensionando se necessário
void Jardineiro::adicionarFerramenta(Ferramenta* f) {
    if (numFerramentas == capacidade) {
        redimensionar();
    }
    ferramentas[numFerramentas] = f;
    numFerramentas++;
}

// Usa a ferramenta "na mão" (a última adicionada)
void Jardineiro::usarFerramenta(Jardim* jardim) {
    if (numFerramentas == 0) return;

    Ferramenta* f = ferramentas[numFerramentas - 1];
    if (f != nullptr && !f->estaDesgastada()) {
        f->usar(jardim, linha, coluna);
    }
}

void Jardineiro::entrar(int lin, int col) {
    linha = lin;
    coluna = col;
}

// Verifica se tem um tipo de ferramenta
bool Jardineiro::temFerramenta(const std::string& tipo) const {
    // Loop 'for' clássico
    for (int i = 0; i < numFerramentas; i++) {
        // Assume que Ferramenta tem getTipo()
        if (ferramentas[i] != nullptr && ferramentas[i]->getTipo() == tipo) {
            return true;
        }
    }
    return false;
}

void Jardineiro::mover(char direcao, int max_lin, int max_col) {
    if (direcao == 'n' && linha > 0) linha--;
    else if (direcao == 's' && linha < max_lin - 1) linha++;
    else if (direcao == 'o' && coluna > 0) coluna--;
    else if (direcao == 'e' && coluna < max_col - 1) coluna++;
}
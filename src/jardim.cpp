#include "../include/jardim.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/Settings.h"
#include "../include/jardineiro.h"
#include "../include/planta.h"
using namespace std;

Jardim::Jardim(int lin, int col) {
    linhas = lin;
    colunas = col;
    // CRIAÇÃO DO JARDINEIRO (Agregação)
    jardineiro = new Jardineiro(-1, -1); // Inicializa fora do jardim

    // Aloca a grelha dinamicamente
    grelha = new Celula*[linhas];
    for (int i = 0; i < linhas; i++) {
        grelha[i] = new Celula[colunas];
    }
    // Inicializa água e nutrientes aleatoriamente
    srand(time(0));
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            grelha[i][j].setAgua(rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1) + Settings::Jardim::agua_min);
            grelha[i][j].setNutrientes(rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1) + Settings::Jardim::nutrientes_min);
        }
    }
}

Jardim::~Jardim() {
    // Libera a memória alocada
    for (int i = 0; i < linhas; i++) {
        delete[] grelha[i];
    }
    delete[] grelha;

    // Libera o Jardineiro (Composição - o Jardim é responsável por ele)
    delete jardineiro;
}

void Jardim::imprimir() {
    cout << "  ";
    for (int j = 0; j < colunas; j++) {
        cout << static_cast<char>('A' + j) << " ";
    }
    cout << endl;

    for (int i = 0; i < linhas; i++) {
        cout << static_cast<char>('A' + i) << " ";
        for (int j = 0; j < colunas; j++) {
            char simbolo = grelha[i][j].getSimbolo();
            // Prioridade do Jardineiro ('*')
            if (jardineiro != nullptr && jardineiro->getLinha() == i && jardineiro->getColuna() == j) {
                cout << "* "; // O enunciado pede '*'
            } else {
                cout << simbolo << " ";
            }
        }
        cout << endl;
    }
}

void Jardim::atualizarInstante() {
    // Lógica de Meta 2 (Simulação)
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            Planta* p = grelha[i][j].getPlanta();
            if (p != nullptr) {
                p->atualizar(this, i, j);
            }
        }
    }
}

bool Jardim::posicaoValida(int lin, int col) const {
    return lin >= 0 && lin < linhas && col >= 0 && col < colunas;
}

Celula& Jardim::getCelula(int lin, int col) {
    return grelha[lin][col];
}

std::string Jardim::posicaoParaString(int lin, int col) const {
    // Retorna a posição em formato de string (ex: "aa")
    return std::string(1, 'a' + lin) + std::string(1, 'a' + col);
}
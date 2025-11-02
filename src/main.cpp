#include <iostream>
#include "../include/comandos.h"
using namespace std;

int main() {
    Comando comando;
    string entrada;

    cout << "=== simulador de jardim ===\n";
    cout << "> ";
    while (getline(cin, entrada) && comando.processar(entrada)) {
        // Pede o próximo comando
        cout << "> ";
    }
    return 0;
}

// Definição explícita de constantes estáticas para resolver o erro de linkagem.
const int Settings::Jardim::agua_min;
const int Settings::Jardim::agua_max;
const int Settings::Jardim::nutrientes_min;
const int Settings::Jardim::nutrientes_max;

// Roseira
const int Settings::Roseira::inicial_agua;
const int Settings::Roseira::inicial_nutrientes;
const int Settings::Roseira::perda_agua;
const int Settings::Roseira::perda_nutrientes;
const int Settings::Roseira::absorcao_agua;
const int Settings::Roseira::absorcao_nutrientes;
const int Settings::Roseira::morre_agua_menor;
const int Settings::Roseira::morre_nutrientes_menor;
const int Settings::Roseira::morre_nutrientes_maior;
const int Settings::Roseira::multiplica_nutrientes_maior;
const int Settings::Roseira::nova_nutrientes;
const int Settings::Roseira::nova_agua_percentagem;
const int Settings::Roseira::original_nutrientes;
const int Settings::Roseira::original_agua_percentagem;

// (Adicionar aqui as definições para Cacto, ErvaDaninha, Regador, Adubo
// se o linker se queixar delas também)
#include "../include/comandos.h"
#include <iostream>
#include <sstream>
// #include <vector> // REMOVIDO
#include <cctype>
#include <stdexcept>

using namespace std;

Comando::~Comando() {
    delete jardim;
}

Coordenadas Comando::stringParaPosicao(const std::string& pos) const {
    Coordenadas resultado;
    if (pos.length() != 2) return resultado;
    if (!std::islower(pos[0]) || !std::islower(pos[1])) {
        return resultado;
    }
    resultado.linha = pos[0] - 'a';
    resultado.coluna = pos[1] - 'a';
    if (resultado.linha >= 26 || resultado.coluna >= 26) {
        return resultado;
    }
    resultado.valida = true;
    return resultado;
}

// Assinatura alterada para bool
bool Comando::processar(const string& comando) {
    if (comando.empty()) return true; // Continua o loop

    // NOVO: Parsing com array estático
    const int MAX_TOKENS = 5; // Limite seguro de palavras por comando
    string tokens[MAX_TOKENS];
    int numTokens = 0;

    stringstream ss(comando);
    string token;
    // Preenche o array de tokens
    while (numTokens < MAX_TOKENS && ss >> token) {
        tokens[numTokens] = token;
        numTokens++;
    }
    if (numTokens == 0) return true;

    string nomeComando = tokens[0];

    // --- 1. VALIDAÇÃO: Comando 'jardim <n> <n>' ---
    if (nomeComando == "jardim") {
        if (jardim != nullptr) {
            cout << "Erro: O jardim ja foi criado. Este comando so pode ser executado uma vez." << endl;
            return true;
        }
        if (numTokens != 3) {
            cout << "Sintaxe invalida para 'jardim'. Uso correto: jardim <linhas> <colunas>" << endl;
            return true;
        }
        try {
            int linhas = stoi(tokens[1]);
            int colunas = stoi(tokens[2]);
            if (linhas < 1 || linhas > 26 || colunas < 1 || colunas > 26) {
                cout << "Erro: Dimensoes invalidas! Insira valores entre 1 e 26." << endl;
                return true;
            }
            jardim = new Jardim(linhas, colunas);
            cout << "\nJardim criado com sucesso: " << linhas << "x" << colunas << "." << endl;
            jardim->imprimir();
        } catch (const std::exception& e) {
            cout << "Erro de sintaxe: As dimensoes devem ser numeros inteiros." << endl;
        }
        return true;
    }

    // --- 2. VALIDAÇÃO: Comando 'sair' ---
    if (nomeComando == "sair") {
        if (numTokens != 1) {
             cout << "Erro: O comando 'sair' nao aceita parametros." << endl;
             return true;
        }
        cout << "Simulacao encerrada. Obrigado!" << endl;
        return false; // <<< ALTERADO: Termina o loop no main
    }

    // --- VERIFICAÇÃO: JARDIM EXISTENTE ---
    if (jardim == nullptr) {
        cout << "Erro: O jardim ainda nao foi criado. Execute 'jardim <L> <C>' primeiro." << endl;
        return true;
    }

    // --- 3. VALIDAÇÃO: Comando 'entra <l><c>' ---
    if (nomeComando == "entra") {
        if (numTokens != 2) {
            cout << "Sintaxe invalida para 'entra'. Uso correto: entra <posicao>" << endl;
            return true;
        }
        string posString = tokens[1];
        Coordenadas pos = stringParaPosicao(posString);
        if (!pos.valida) {
            cout << "Erro: Posicao '" << posString << "' em formato invalido. Use duas letras (ex: aa)." << endl;
            return true;
        }
        if (!jardim->posicaoValida(pos.linha, pos.coluna)) {
            cout << "Erro: Posicao '" << posString << "' esta fora dos limites do jardim ("
                 << jardim->posicaoParaString(jardim->getLinhas() - 1, jardim->getColunas() - 1) << ")." << endl;
            return true;
        }
        cout << "Validado! Jardineiro pronto para entrar na posicao " << posString << "." << endl;
        jardim->imprimir();
        return true;

    // --- 4. VALIDAÇÃO: Comando 'avanca [n]' ---
    } else if (nomeComando == "avanca") {
        if (numTokens > 2) {
            cout << "Sintaxe invalida para 'avanca'. Uso correto: avanca [n]" << endl;
            return true;
        }
        int instantes = 1;
        if (numTokens == 2) {
            try {
                instantes = stoi(tokens[1]);
                if (instantes <= 0) {
                    cout << "Erro: O numero de instantes deve ser um valor inteiro positivo." << endl;
                    return true;
                }
            } catch (const std::exception& e) {
                cout << "Erro: O parametro para 'avanca' deve ser um numero inteiro." << endl;
                return true;
            }
        }
        cout << "Validado! Avancando " << instantes << " instante(s)..." << endl;
        jardim->imprimir();
        return true;

    } else if (nomeComando == "planta") {
        if (numTokens != 3) {
            cout << "Erro: uso correto: planta <pos> <tipo>" << endl;
            cout << "Exemplo: planta aa cacto" << endl;
            return true;
        }
        // ... (A lógica de validação do 'planta' viria aqui) ...
        return true;

    } else {
        cout << "Comando invalido! '" << nomeComando << "' nao e um comando reconhecido." << endl;
    }

    return true; // Garante que o loop continua
}
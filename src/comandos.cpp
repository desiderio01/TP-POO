#include "../include/comandos.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <stdexcept>

using namespace std;

// Implementação do Destrutor
Comando::~Comando() {
    delete jardim;
}

// Função Auxiliar: Tokenização (Parsing)
std::vector<std::string> Comando::parseComando(const std::string& comando) const {
    stringstream ss(comando);
    vector<string> tokens;
    string token;

    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Função Auxiliar: Conversão de Posição ("ej" -> 4, 9)
Coordenadas Comando::stringParaPosicao(const std::string& pos) const {
    Coordenadas resultado;
    if (pos.length() != 2) return resultado;
    if (!std::islower(pos[0]) || !std::islower(pos[1])) {
        // Erro: posição deve ser em minúsculas (conforme regra do enunciado)
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

void Comando::processar(const string& comando) {
    if (comando.empty()) return;
    vector<string> tokens = parseComando(comando);
    if (tokens.empty()) return;
    string nomeComando = tokens[0];
    // --- 1. VALIDAÇÃO: Comando 'jardim <n> <n>' ---
    if (nomeComando == "jardim") {
        if (jardim != nullptr) {
            cout << "Erro: O jardim ja foi criado. Este comando so pode ser executado uma vez." << endl;
            return;
        }
        if (tokens.size() != 3) {
            cout << "Sintaxe invalida para 'jardim'. Uso correto: jardim <linhas> <colunas>" << endl;
            return;
        }
        try {
            int linhas = stoi(tokens[1]);
            int colunas = stoi(tokens[2]);
            if (linhas < 1 || linhas > 26 || colunas < 1 || colunas > 26) {
                cout << "Erro: Dimensoes invalidas! Insira valores entre 1 e 26." << endl;
                return;
            }
            jardim = new Jardim(linhas, colunas);
            cout << "\nJardim criado com sucesso: " << linhas << "x" << colunas << "." << endl;
            jardim->imprimir();
        } catch (const std::exception& e) {
            cout << "Erro de sintaxe: As dimensoes devem ser numeros inteiros." << endl;
        }
        return;
    }
    // --- 2. VALIDAÇÃO: Comando 'sair' ---
    if (nomeComando == "sair") {
        if (tokens.size() != 1) {
             cout << "Erro: O comando 'sair' nao aceita parametros." << endl;
             return;
        }
        cout << "Simulacao encerrada. Obrigado!" << endl;
        exit(0);
    }
    // --- VERIFICAÇÃO: JARDIM EXISTENTE ---
    if (jardim == nullptr) {
        cout << "Erro: O jardim ainda nao foi criado. Execute 'jardim <L> <C>' primeiro." << endl;
        return;
    }
    // --- 3. VALIDAÇÃO: Comando 'entra <l><c>' ---
    if (nomeComando == "entra") {
        if (tokens.size() != 2) {
            cout << "Sintaxe invalida para 'entra'. Uso correto: entra <posicao>" << endl;
            return;
        }
        string posString = tokens[1];
        Coordenadas pos = stringParaPosicao(posString);
        if (!pos.valida) {
            cout << "Erro: Posicao '" << posString << "' em formato invalido. Use duas letras (ex: aa)." << endl;
            return;
        }
        // Validação Semântica: Posicao nos limites do jardim atual
        if (!jardim->posicaoValida(pos.linha, pos.coluna)) {
            cout << "Erro: Posicao '" << posString << "' esta fora dos limites do jardim ("
                 << jardim->posicaoParaString(jardim->getLinhas() - 1, jardim->getColunas() - 1) << ")." << endl;
            return;
        }
        cout << "Validado! Jardineiro pronto para entrar na posicao " << posString << "." << endl;
        jardim->imprimir();
    // --- 4. VALIDAÇÃO: Comando 'avanca [n]' ---
    } else if (nomeComando == "avanca") {
        if (tokens.size() > 2) {
            cout << "Sintaxe invalida para 'avanca'. Uso correto: avanca [n]" << endl;
            return;
        }
        int instantes = 1;
        if (tokens.size() == 2) {
            try {
                instantes = stoi(tokens[1]);
                if (instantes <= 0) {
                    cout << "Erro: O numero de instantes deve ser um valor inteiro positivo." << endl;
                    return;
                }
            } catch (const std::exception& e) {
                cout << "Erro: O parametro para 'avanca' deve ser um numero inteiro." << endl;
                return;
            }
        }
        cout << "Validado! Avancando " << instantes << " instante(s)..." << endl;
        jardim->imprimir();
    }else if (nomeComando == "planta") {
        if (tokens.size() != 3) {
            cout << "Erro: uso correto: planta <pos> <tipo>" << endl;
            cout << "Exemplo: planta aa cacto" << endl;
            return;
        }
    } else {
        cout << "Comando invalido! '" << nomeComando << "' nao e um comando reconhecido." << endl;
    }
}
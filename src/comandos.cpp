#include "../include/comandos.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

Comando::~Comando() {
    delete jardim;
}

Coordenadas Comando::stringParaPosicao(const std::string& pos) const {
    Coordenadas resultado;
    if (pos.length() != 2) return resultado;
    if ((pos[0] < 'a' || pos[0] > 'z') || (pos[1] < 'a' || pos[1] > 'z')) {
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

bool Comando::processar(const string& comando) {
    if (comando.empty()) return true; // Continua o loop

    // Parsing com array estático
    const int MAX_TOKENS = 5;
    string tokens[MAX_TOKENS];
    int numTokens = 0;

    stringstream ss(comando);
    string token;
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
        int linhas, colunas;
        stringstream ss_linhas(tokens[1]);
        stringstream ss_colunas(tokens[2]);

        // Tenta extrair os números. Se falhar (ou se sobrar lixo, ex: "10a") dá erro.
        if (!(ss_linhas >> linhas) || !(ss_colunas >> colunas) || !ss_linhas.eof() || !ss_colunas.eof()) {
            cout << "Erro de sintaxe: As dimensoes devem ser numeros inteiros." << endl;
            return true;
        }

        // Lógica original de validação
        if (linhas < 1 || linhas > 26 || colunas < 1 || colunas > 26) {
            cout << "Erro: Dimensoes invalidas! Insira valores entre 1 e 26." << endl;
            return true;
        }
        jardim = new Jardim(linhas, colunas);
        cout << "\nJardim criado com sucesso: " << linhas << "x" << colunas << "." << endl;
        jardim->imprimir();
        return true;
    }
    // --- 2. VALIDAÇÃO: Comando 'sair' e 'fim' ---
    if (nomeComando == "sair" || nomeComando == "fim") { //

        if (numTokens != 1) {
            cout << "Erro: O comando '" << nomeComando << "' nao aceita parametros." << endl;
            return true;
        }
        cout << "Simulacao encerrada. Obrigado!" << endl;
        return false; // Termina o loop no main
    }

    // --- VERIFICAÇÃO: JARDIM EXISTENTE ---
    if (jardim == nullptr) {
        // Permite apenas o comando 'executa' antes do 'jardim'
        if (nomeComando == "executa") { //
            if (numTokens != 2) {
                cout << "Sintaxe invalida. Uso correto: executa <nome-do-ficheiro>" << endl;
                return true;
            }
            cout << "Validado! Pronto para executar ficheiro '" << tokens[1] << "'." << endl;
            return true;
        }
        cout << "Erro: O jardim ainda nao foi criado. Execute 'jardim <L> <C>' primeiro." << endl;
        return true;
    }

    // --- 3. VALIDAÇÃO: Comando 'entra <l><c>' ---
    if (nomeComando == "entra") {
        if (numTokens != 2) {
            cout << "Sintaxe invalida para 'entra'. Uso correto: entra <posicao> (ex: entra fg)" << endl;
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
            stringstream ss_instantes(tokens[1]);

            if (!(ss_instantes >> instantes) || !ss_instantes.eof()) {
                cout << "Erro: O parametro para 'avanca' deve ser um numero inteiro." << endl;
                return true;
            }

            if (instantes <= 0) {
                cout << "Erro: O numero de instantes deve ser um valor inteiro positivo." << endl;
                return true;
            }
        }
        cout << "Validado! Avancando " << instantes << " instante(s)..." << endl;
        jardim->imprimir();
        return true;

    // --- 5. VALIDAÇÃO: Comando 'planta <l><c> <tipo>' ---
    } else if (nomeComando == "planta") {
        if (numTokens != 3) {
            cout << "Sintaxe invalida para 'planta'. Uso correto: planta <posicao> <tipo> (ex: planta fb c)" << endl;
            return true;
        }
        string posString = tokens[1];
        string tipoString = tokens[2];
        Coordenadas pos = stringParaPosicao(posString);
        if (!pos.valida) {
            cout << "Erro: Posicao '" << posString << "' em formato invalido. Use duas letras (ex: aa)." << endl;
            return true;
        }
        if (!jardim->posicaoValida(pos.linha, pos.coluna)) {
            cout << "Erro: Posicao '" << posString << "' esta fora dos limites do jardim." << endl;
            return true;
        }
        if (tipoString.length() != 1 || (tipoString != "c" && tipoString != "r" && tipoString != "e" && tipoString != "x")) {
            cout << "Erro: Tipo de planta '" << tipoString << "' invalido. Use 'c', 'r', 'e' ou 'x'." << endl;
            return true;
        }
        cout << "Validado! Planta '" << tipoString << "' pronta para ser plantada na posicao " << posString << "." << endl;
        jardim->imprimir();
        return true;

    // --- 6. VALIDAÇÃO: Comando 'colhe <l><c>' ---
    } else if (nomeComando == "colhe") {
        if (numTokens != 2) {
            cout << "Sintaxe invalida para 'colhe'. Uso correto: colhe <posicao> (ex: colhe fb)" << endl;
            return true;
        }
        string posString = tokens[1];
        Coordenadas pos = stringParaPosicao(posString);
        if (!pos.valida) {
            cout << "Erro: Posicao '" << posString << "' em formato invalido. Use duas letras (ex: aa)." << endl;
            return true;
        }
        if (!jardim->posicaoValida(pos.linha, pos.coluna)) {
            cout << "Erro: Posicao '" << posString << "' esta fora dos limites do jardim." << endl;
            return true;
        }
        cout << "Validado! Pronto para colher na posicao " << posString << "." << endl;
        jardim->imprimir();
        return true;

    // --- 7. VALIDAÇÃO: Comando 'lplanta <l><c>' ---
    } else if (nomeComando == "lplanta") {
        if (numTokens != 2) {
            cout << "Sintaxe invalida para 'lplanta'. Uso correto: lplanta <posicao> (ex: lplanta ej)" << endl;
            return true;
        }
        string posString = tokens[1];
        Coordenadas pos = stringParaPosicao(posString);
        if (!pos.valida) {
            cout << "Erro: Posicao '" << posString << "' em formato invalido. Use duas letras (ex: aa)." << endl;
            return true;
        }
        if (!jardim->posicaoValida(pos.linha, pos.coluna)) {
            cout << "Erro: Posicao '" << posString << "' esta fora dos limites do jardim." << endl;
            return true;
        }
        cout << "Validado! Pronto para listar a planta na posicao " << posString << "." << endl;
        return true;

    // --- 8. VALIDAÇÃO: Comando 'lsolo <l><c> [n]' ---
    } else if (nomeComando == "lsolo") {
        if (numTokens < 2 || numTokens > 3) {
            cout << "Sintaxe invalida para 'lsolo'. Uso correto: lsolo <posicao> [raio]" << endl;
            return true;
        }
        string posString = tokens[1];
        Coordenadas pos = stringParaPosicao(posString);
        if (!pos.valida) {
            cout << "Erro: Posicao '" << posString << "' em formato invalido. Use duas letras (ex: aa)." << endl;
            return true;
        }
        if (!jardim->posicaoValida(pos.linha, pos.coluna)) {
            cout << "Erro: Posicao '" << posString << "' esta fora dos limites do jardim." << endl;
            return true;
        }
        int raio = 0;
        if (numTokens == 3) {
            try {
                raio = stoi(tokens[2]);
                if (raio < 0) {
                    cout << "Erro: O raio [n] deve ser um valor inteiro positivo ou zero." << endl;
                    return true;
                }
            } catch (const std::exception& e) {
                cout << "Erro: O parametro [n] para 'lsolo' deve ser um numero inteiro." << endl;
                return true;
            }
        }
        cout << "Validado! Pronto para listar o solo na posicao " << posString << " com raio " << raio << "." << endl;
        return true;

    // --- 9. VALIDAÇÃO: Comandos de 1 Token (Listar/Ação) ---
    } else if (nomeComando == "lplantas" || nomeComando == "larea" || nomeComando == "lferr" || nomeComando == "larga" || nomeComando == "sai") { //
        if (numTokens != 1) {
            cout << "Sintaxe invalida: O comando '" << nomeComando << "' nao aceita parametros." << endl;
            return true;
        }
        cout << "Validado! Pronto para executar '" << nomeComando << "'." << endl;
        return true;

    // --- 10. VALIDAÇÃO: Comandos de Movimento ---
    } else if (nomeComando == "e" || nomeComando == "d" || nomeComando == "c" || nomeComando == "b") { //
        if (numTokens != 1) {
            cout << "Sintaxe invalida: O comando '" << nomeComando << "' nao aceita parametros." << endl;
            return true;
        }
        cout << "Validado! Pronto para mover '" << nomeComando << "'." << endl;
        jardim->imprimir();
        return true;

    // --- 11. VALIDAÇÃO: Comando 'pega <n>' ---
    } else if (nomeComando == "pega") { //
        if (numTokens != 2) {
            cout << "Sintaxe invalida para 'pega'. Uso correto: pega <numero_serie>" << endl;
            return true;
        }
        try {
            int n_serie = stoi(tokens[1]);
            if (n_serie <= 0) {
                cout << "Erro: O numero de serie deve ser um inteiro positivo." << endl;
                return true;
            }
            cout << "Validado! Pronto para pegar a ferramenta " << n_serie << "." << endl;
        } catch (const std::exception& e) {
            cout << "Erro: O numero de serie deve ser um numero inteiro." << endl;
        }
        return true;

    // --- 12. VALIDAÇÃO: Comando 'compra <c>' ---
    } else if (nomeComando == "compra") { //
        if (numTokens != 2) {
            cout << "Sintaxe invalida para 'compra'. Uso correto: compra <tipo>" << endl;
            return true;
        }
        string tipoFerramenta = tokens[1];
        if (tipoFerramenta.length() != 1 || (tipoFerramenta != "g" && tipoFerramenta != "a" && tipoFerramenta != "t" && tipoFerramenta != "z")) { //
            cout << "Erro: Tipo de ferramenta '" << tipoFerramenta << "' invalido. Use 'g', 'a', 't' ou 'z'." << endl;
            return true;
        }
        cout << "Validado! Pronto para comprar '" << tipoFerramenta << "'." << endl;
        return true;

    // --- 13. VALIDAÇÃO: Comandos de Ficheiro/Memória ---
    } else if (nomeComando == "grava" || nomeComando == "recupera" || nomeComando == "apaga") { //
        if (numTokens != 2) {
            cout << "Sintaxe invalida. Uso correto: " << nomeComando << " <nome>" << endl;
            return true;
        }
        cout << "Validado! Pronto para " << nomeComando << " '" << tokens[1] << "'." << endl;
        return true;

    } else {
        cout << "Comando invalido! '" << nomeComando << "' nao e um comando reconhecido." << endl;
    }
    return true; // Garante que o loop continua
}
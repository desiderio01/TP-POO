#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
#include <vector> // Necessário para o parsing
#include "jardim.h"
#include "comandos.h"

struct Coordenadas {
    int linha = -1;
    int coluna = -1;
    bool valida = false;
};
class Comando {
private:
    Jardim* jardim = nullptr;
    std::vector<std::string> parseComando(const std::string& comando) const;
    Coordenadas stringParaPosicao(const std::string& pos) const;
public:
    Comando() = default; // Novo construtor default
    ~Comando(); // Necessário para libertar o Jardim (se criado)

    void processar(const std::string& comando);
};

#endif //COMANDOS_H
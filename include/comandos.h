#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
#include "jardim.h"

struct Coordenadas {
    int linha = -1;
    int coluna = -1;
    bool valida = false;
};

class Comando {
private:
    Jardim* jardim = nullptr;
    Coordenadas stringParaPosicao(const std::string& pos) const;
public:
    Comando() = default;
    ~Comando();

    bool processar(const std::string& comando);
};

#endif //COMANDOS_H
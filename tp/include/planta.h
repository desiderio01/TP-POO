// include/planta.h

#ifndef PLANTA_H
#define PLANTA_H

#include "Settings.h"

class Jardim; // Necessário para a assinatura de atualizar

class Planta {
protected:
    int agua_interna;
    int nutrientes_interna;
    int idade;

public:
    Planta(int agua_inicial, int nut_inicial);
    virtual ~Planta() = default;

    virtual char getSimbolo() const = 0;

    virtual void atualizar(Jardim* jardim, int lin, int col) = 0;

    int getAguaInterna() const { return agua_interna; }
    int getNutrientesInterna() const { return nutrientes_interna; }
    int getIdade() const { return idade; }

    void envelhecer() { idade++; }
};

#endif // PLANTA_H
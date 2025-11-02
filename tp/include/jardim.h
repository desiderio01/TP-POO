#ifndef JARDIM_H
#define JARDIM_H

#include "celula.h"
#include <string>

class Jardineiro; // Forward Declaration
class Jardim {
private:
    Celula** grelha;
    int linhas;
    int colunas;
    Jardineiro* jardineiro = nullptr; // NOVO: Agregação do Jardineiro (Meta 1)

public:
    //inicializa a grelha com o tamanho especificado
    Jardim(int lin, int col);

    //libera a memória alocada
    ~Jardim();

    //imprimir a grelha com a régua
    void imprimir();

    // NOVO: Getters para as dimensões (CRÍTICO para a validação de comandos)
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }

    // Corrigido: A assinatura deve ser apenas declarada no .h (implementação no .cpp)
    void atualizarInstante();

    bool posicaoValida(int lin, int col) const;
    Celula& getCelula(int lin, int col);
    void adicionarPlanta(const std::string& tipo, const std::string& pos);
    std::string posicaoParaString(int lin, int col) const;
};

#endif //JARDIM_H
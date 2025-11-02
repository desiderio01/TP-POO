#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <string>

class Ferramenta;
class Jardim;

class Jardineiro {
private:
    int linha, coluna;

    Ferramenta** ferramentas; // Array dinâmico de ponteiros para Ferramenta
    int numFerramentas;       // Número de ferramentas atuais
    int capacidade;           // Tamanho alocado do array 'ferramentas'

    void redimensionar();

public:
    Jardineiro(int lin, int col);
    ~Jardineiro();

    Jardineiro(const Jardineiro& outro) = delete;
    Jardineiro& operator=(const Jardineiro& outro) = delete;

    // Getters
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }

    // Movimentação
    void mover(char direcao, int max_lin, int max_col);
    void entrar(int lin, int col);

    // Ferramentas (assinaturas iguais, implementação muda)
    void adicionarFerramenta(Ferramenta* f);
    void usarFerramenta(Jardim* jardim);
    bool temFerramenta(const std::string& tipo) const;
};

#endif // JARDINEIRO_H
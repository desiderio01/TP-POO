#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <vector>
#include <string>

class Ferramenta;
class Jardim;

class Jardineiro {
private:
    int linha, coluna;
    std::vector<Ferramenta*> ferramentas;  // Conjunto de ferramentas

public:
    Jardineiro(int lin, int col);
    ~Jardineiro();

    // Getters
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }

    // Movimentação
    void mover(char direcao, int max_lin, int max_col);
    void entrar(int lin, int col);
    // Ferramentas
    void adicionarFerramenta(Ferramenta* f);
    void usarFerramenta(Jardim* jardim);  // Usa a última ferramenta (na mão)
    bool temFerramenta(const std::string& tipo) const;
};

#endif // JARDINEIRO_H
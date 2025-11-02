#ifndef ADUBO_H
#define ADUBO_H

#include "ferramenta.h"

class Adubo : public Ferramenta {
public:
    Adubo();
    void usar(Jardim* jardim, int lin, int col) override;
};

#endif // ADUBO_H

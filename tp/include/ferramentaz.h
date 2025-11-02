#ifndef FERRAMENTAZ_H
#define FERRAMENTAZ_H

#include "ferramenta.h"

class FerramentaZ : public Ferramenta {
public:
    FerramentaZ();
    void usar(Jardim* jardim, int lin, int col) override;
};

#endif // FERRAMENTAZ_H
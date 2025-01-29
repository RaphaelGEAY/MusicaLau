#ifndef ELECTRONIQUE_HPP
#define ELECTRONIQUE_HPP

#include "Instrument.hpp"

using namespace std;

class Electronique : public Instrument {
public:
    Electronique();
    int modeInteractif() const override;
};

#endif

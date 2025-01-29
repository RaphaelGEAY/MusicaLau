#ifndef GUITARE_HPP
#define GUITARE_HPP

#include "Instrument.hpp"

using namespace std;

class Guitare : public Instrument {
public:
    Guitare();
    int modeInteractif() const override;
};

#endif

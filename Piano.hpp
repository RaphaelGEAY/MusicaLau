#ifndef PIANO_HPP
#define PIANO_HPP

#include "Instrument.hpp"

using namespace std;

class Piano : public Instrument {
public:
    Piano();
    int modeInteractif() const;
};

#endif

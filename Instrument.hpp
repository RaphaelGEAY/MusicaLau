#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include <string>

using namespace std;

class Instrument {
protected: // Permet d'être accessible dans les classes hérités
    string nom;
public:
    Instrument(const string nomInstrument);
    virtual int modeInteractif() const; // Permet la redéfinition dans les classes hérités
};

#endif

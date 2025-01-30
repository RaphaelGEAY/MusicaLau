#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include <string>

using namespace std;

class Instrument {
protected: // Permet d'�tre accessible dans les classes h�rit�s
    string nom;
public:
    Instrument(const string nomInstrument);
    virtual int modeInteractif() const; // Permet la red�finition dans les classes h�rit�s
};

#endif

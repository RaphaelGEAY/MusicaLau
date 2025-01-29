#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include <string>

using namespace std;

class Instrument {
protected:
    string nom;
public:
    Instrument(const string& nomInstrument);
    virtual int modeInteractif() const = 0;
    virtual ~Instrument() = default;
};

#endif

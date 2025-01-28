#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include <string>
#include <iostream>

class Instrument {
protected:
    std::string nom;
public:
    Instrument(const std::string& nomInstrument);
    virtual void jouerNote(const std::string& note) const = 0;
    virtual void afficher() const = 0;
    virtual int modeInteractif() const = 0;
    virtual ~Instrument() = default;
};

#endif

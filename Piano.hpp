#ifndef PIANO_HPP
#define PIANO_HPP

#include "Instrument.hpp"
#include <string>

class Piano : public Instrument {
public:
    Piano();
    void jouerNote(const std::string& note) const override;
    void afficher() const override;
    int modeInteractif() const override;
};

#endif

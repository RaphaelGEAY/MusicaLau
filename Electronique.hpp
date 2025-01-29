#ifndef ELECTRONIQUE_HPP
#define ELECTRONIQUE_HPP

#include "Instrument.hpp"

class Electronique : public Instrument {
public:
    Electronique();
    void jouerNote(const std::string& note) const override;
    void afficher() const override;
    int modeInteractif() const override;
};

#endif

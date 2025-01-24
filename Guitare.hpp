#ifndef GUITARE_HPP
#define GUITARE_HPP

#include "Instrument.hpp"

class Guitare : public Instrument {
public:
    Guitare();
    void jouerNote(const std::string& note) const override;
    void afficher() const override;
};

#endif

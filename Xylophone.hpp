#ifndef XYLOPHONE_HPP
#define XYLOPHONE_HPP

#include "Instrument.hpp"

class Xylophone : public Instrument {
public:
    Xylophone();
    void jouerNote(const std::string& note) const override;
    void afficher() const override;
};

#endif

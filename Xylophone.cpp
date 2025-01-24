#include "Xylophone.hpp"

Xylophone::Xylophone() : Instrument("Xylophone") {}

void Xylophone::jouerNote(const std::string& note) const {
    std::cout << "Xylophone joue : " << note << std::endl;
}

void Xylophone::afficher() const {
    std::cout << "Instrument : " << nom << std::endl;
}

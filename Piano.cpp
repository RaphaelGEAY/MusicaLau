#include "Piano.hpp"

Piano::Piano() : Instrument("Piano") {}

void Piano::jouerNote(const std::string& note) const {
    std::cout << "Piano joue : " << note << std::endl;
}

void Piano::afficher() const {
    std::cout << "Instrument : " << nom << std::endl;
}

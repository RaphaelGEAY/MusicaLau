#include "Guitare.hpp"

Guitare::Guitare() : Instrument("Guitare") {}

void Guitare::jouerNote(const std::string& note) const {
    std::cout << "Guitare joue : " << note << std::endl;
}

void Guitare::afficher() const {
    std::cout << "Instrument : " << nom << std::endl;
}

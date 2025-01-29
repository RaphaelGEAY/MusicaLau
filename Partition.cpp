#include "Partition.hpp"
#include <iostream>

void Partition::chargerPartition(const std::string& nomFichier) {
    notes = { "do", "re", "mi", "fa", "sol" };
    std::cout << "Partition chargée depuis : " << nomFichier << std::endl;
}

void Partition::jouer(const Instrument& instrument, const std::string& rythme) const {
    std::cout << "Joue avec rythme : " << rythme << std::endl;
    for (const auto& note : notes) {
        instrument.jouerNote(note);
    }
}

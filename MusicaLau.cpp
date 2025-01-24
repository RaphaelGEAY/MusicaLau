#include <iostream>
#include "Piano.hpp"
#include "Xylophone.hpp"
#include "Guitare.hpp"
#include "Partition.hpp"

void afficherMenu() {
    std::cout << "\n--- Menu Principal ---\n";
    std::cout << "1. Choisir un instrument\n";
    std::cout << "2. Jouer une musique\n";
    std::cout << "3. Quitter\n";
    std::cout << "Votre choix : ";
}

void afficherInstruments() {
    std::cout << "\n--- Choisir un Instrument ---\n";
    std::cout << "1. Piano\n";
    std::cout << "2. Xylophone\n";
    std::cout << "3. Guitare\n";
    std::cout << "Votre choix : ";
}

int main() {
    Instrument* instrument = nullptr;
    std::string choixMenu;
    std::string choixInstrument;

    while (true) {
        afficherMenu();
        std::cin >> choixMenu;

        if (choixMenu == "1") {
            afficherInstruments();
            std::cin >> choixInstrument;

            if (choixInstrument == "1") {
                instrument = new Piano();
            }
            else if (choixInstrument == "2") {
                instrument = new Xylophone();
            }
            else if (choixInstrument == "3") {
                instrument = new Guitare();
            }
            else {
                std::cout << "Choix invalide. Aucun instrument sélectionné.\n";
                instrument = nullptr;
            }

            if (instrument) {
                instrument->afficher();
            }

        }
        else if (choixMenu == "2") {
            if (!instrument) {
                std::cout << "Aucun instrument sélectionné. Veuillez d'abord en choisir un.\n";
            }
            else {
                Partition partition;
                partition.chargerPartition("partition.txt");
                partition.jouer(*instrument, "normal");
            }

        }
        else if (choixMenu == "3") {
            std::cout << "Au revoir !\n";
            break;

        }
        else {
            std::cout << "Choix invalide. Veuillez réessayer.\n";
        }
    }

    delete instrument;
    return 0;
}

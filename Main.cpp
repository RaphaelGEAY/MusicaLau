#define SDL_MAIN_HANDLED
#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"
#include "Piano.hpp"
#include "Guitare.hpp"
#include "Electronique.hpp"
#include "Partition.hpp"
#include "Fonctions_audio.hpp"

using namespace std;

void afficherMenu() {
    for (int i = 0; i < 100; i++) {
        cout << endl;
    }
    cout << "\n--- Menu Principal ---\n" << endl;
    cout << "1. Choisir un instrument\n";
    cout << "2. Jouer une musique\n";
    cout << "3. Quitter\n" << endl;
    cout << "Choix : ";
    for (int i = 0; i < 20; i++) {
        cout << endl;
    }
}

void afficherInstruments() {
    for (int i = 0; i < 100; i++) {
        cout << endl;
    }
    cout << "\n--- Choisir un Instrument ---\n" << endl;
    cout << "1. Piano\n";
    cout << "2. Guitare\n";
    cout << "3. Electronique\n" << endl;
    cout << "Choix : ";
    for (int i = 0; i < 20; i++) {
        cout << endl;
    }
}

void afficherModes() {
    for (int i = 0; i < 100; i++) {
        cout << endl;
    }
    cout << "\n--- Choisir un Mode ---\n" << endl;
    cout << "1. Jouer\n";
    cout << "2. Lire\n" << endl;
    cout << "Choix : ";
    for (int i = 0; i < 20; i++) {
        cout << endl;
    }
}

void afficherLectures() {
    for (int i = 0; i < 100; i++) {
        cout << endl;
    }
    cout << "\n--- Choisir une partition ---\n" << endl;
    cout << "1. Mario\n";
    cout << "2. StarWars\n";
    cout << "3. Notes Aléatoires\n" << endl;
    cout << "Choix : ";
    for (int i = 0; i < 20; i++) {
        cout << endl;
    }
}

int main() {

    Instrument* instrument = nullptr;
    string choixMenu;
    string choixInstrument;
    string choixModes;
    string choixLectures;

    while (true) {
        afficherMenu();
        cin >> choixMenu;

        if (choixMenu == "1") {
            afficherInstruments();
            std::cin >> choixInstrument;

            if (choixInstrument == "1") {
                instrument = new Piano();
                afficherModes();
                cin >> choixModes;

                if (choixModes == "1") {
                    instrument->modeInteractif();
                    delete instrument;
                }
            }
            else if (choixInstrument == "2") {
                instrument = new Guitare();
                afficherModes();
                cin >> choixModes;

                if (choixModes == "1") {
                    instrument->modeInteractif();
                    delete instrument;
                }
            }
            else if (choixInstrument == "3") {
                instrument = new Electronique();
                afficherModes();
                cin >> choixModes;

                if (choixModes == "1") {
                    instrument->modeInteractif();
                    delete instrument;
                }
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

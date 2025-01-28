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

void afficherModes() {
    std::cout << "\n--- Choisir un Mode ---\n";
    std::cout << "1. Lire\n";
    std::cout << "2. Jouer\n";
    std::cout << "Votre choix : ";
}

void afficherLectures() {
    std::cout << "\n--- Choisir un Mode ---\n";
    std::cout << "1. Mario\n";
    std::cout << "2. StarWars\n";
    std::cout << "3. Notes Aléatoires\n";
    std::cout << "Votre choix : ";
}

void testSound() {
    Mix_Chunk* sound = Mix_LoadWAV("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\C.wav");

    Mix_PlayChannel(-1, sound, 0);
    SDL_Delay(2000);

    Mix_FreeChunk(sound);
    Mix_CloseAudio();
    SDL_Quit();
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
                if (choixModes == "2") {
                    instrument->modeInteractif();
                    delete instrument;
                }
            }
            else if (choixInstrument == "2") {
                instrument = new Guitare();
            }
            else if (choixInstrument == "3") {
                instrument = new Electronique();
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

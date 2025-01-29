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

// Affichage du menu princpale
void afficherMenu() {
    for (int i = 0; i < 100; i++) {
        cout << endl;
    }
    cout << "Bienvenue dans le magasin de Raphael et Hugo : MusicaLau\n" << endl;
    cout << "--- Que voulez vous faire ---\n" << endl;
    cout << "1. Jouer d'un instrument\n";
    cout << "2. Lire une partition\n";
    cout << "3. Quitter\n" << endl;
    cout << "Choix : ";
    for (int i = 0; i < 20; i++) {
        cout << endl;
    }
}

// Affichage des instruments
void afficherInstruments() {
    for (int i = 0; i < 100; i++) {
        cout << endl;
    }
    cout << "--- Choisir un instrument ---\n" << endl;
    cout << "1. Piano          2 000 Euros\n";
    cout << "2. Guitare        500 Euros\n";
    cout << "3. Electronique   300 Euros\n" << endl;
    cout << "R. Retour\n" << endl;
    cout << "Choix : ";
    for (int i = 0; i < 20; i++) {
        cout << endl;
    }
}

// Affichage des partitions
void afficherPartitions() {
    for (int i = 0; i < 100; i++) {
        cout << endl;
    }
    cout << "--- Choisir une partition ---\n" << endl;
    cout << "1. Mario\n";
    cout << "2. StarWars\n" << endl;
    cout << "R. Retour\n" << endl;
    cout << "Choix : ";
    for (int i = 0; i < 20; i++) {
        cout << endl;
    }
}

// Fonction main
int main() {

    // Initialisation des variables
    Instrument* instrument = nullptr;
    Partition* partition = nullptr;
    string choixMenu;
    string choixInstrument;
    string choixPartition;

    // Boucle principale avec les choix des menus
    while (true) {
        afficherMenu();
        cin >> choixMenu;

        if (choixMenu == "1") {
            afficherInstruments();
            cin >> choixInstrument;

            if (choixInstrument == "1") {
                for (int i = 0; i < 100; i++) {
                    cout << endl;
                }
                instrument = new Piano();
                instrument->modeInteractif();
            }
            else if (choixInstrument == "2") {
                for (int i = 0; i < 100; i++) {
                    cout << endl;
                }
                instrument = new Guitare();
                instrument->modeInteractif();
            }
            else if (choixInstrument == "3") {
                for (int i = 0; i < 100; i++) {
                    cout << endl;
                }
                instrument = new Electronique();
                instrument->modeInteractif();
            }
        }
        else if (choixMenu == "2") {
            afficherPartitions();
            cin >> choixPartition;
            partition = new Partition();

            if (choixPartition == "1") {
                for (int i = 0; i < 100; i++) {
                    cout << endl;
                }
                partition->jouerMario();
            }
            if (choixPartition == "2") {
                for (int i = 0; i < 100; i++) {
                    cout << endl;
                }
                partition->jouerStarWars();
            }
        }
        else if (choixMenu == "3") {
            for (int i = 0; i < 100; i++) {
                cout << endl;
            }
            cout << "Merci et a bientot !";
            for (int i = 0; i < 26; i++) {
                cout << endl;
            }
            break;
        }
    }
    return 0;
}

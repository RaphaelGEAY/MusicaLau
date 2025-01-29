#include "Partition.hpp"
#include "Fonctions_audio.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int Partition::jouerMario() const {

    // D�finir une structure pour la note et sa dur�e
    struct Note {
        string note;
        float duration;
    };

    if (!initSDL()) {
        return 1;
    }

    // D�finir la m�lodie de Mario
    vector<Note> melody = {
        {"E7", 0.083}, {"0", 0.083}, {"E7", 0.083}, {"0", 0.083}, {"0", 0.083},
        {"0", 0.083}, {"E7", 0.083}, {"0", 0.083}, {"0", 0.083}, {"0", 0.083},
        {"C7", 0.083}, {"0", 0.083}, {"E7", 0.083}, {"0", 0.083}, {"0", 0.083},
        {"0", 0.083}, {"G7", 0.083}, {"0", 0.083}, {"0", 0.083}, {"0", 0.083},
        {"0", 0.083}, {"0", 0.099}, {"G6", 0.083}, {"0", 0.500}, {"C7", 0.083},
        {"0", 0.400}, {"G6", 0.083}, {"0", 0.400}, {"E6", 0.083}, {"0", 0.260},
        {"A6", 0.099}, {"0", 0.220}, {"B6", 0.111}, {"0", 0.190}, {"A#6", 0.083},
        {"0", 0.111}, {"A6", 0.083}, {"0", 0.111}, {"G6", 0.083}, {"0", 0.120},
        {"E7", 0.083}, {"0", 0.120}, {"G7", 0.150}, {"0", 0.083}, {"A7", 0.120},
        {"0", 0.190}, {"F7", 0.150}, {"0", 0.083}, {"G7", 0.120}, {"0", 0.200},
        {"E7", 0.111}, {"0", 0.200}, {"C7", 0.083}, {"0", 0.100}, {"D7", 0.083},
        {"0", 0.100}, {"B6", 0.111}
    };

    // Parcours de chaque note dans la m�lodie
    for (const auto& note : melody) {

        int frequency = noteToFrequency(note.note);  // Obtenir la fr�quence de la note
        int toneLength = static_cast<int>(note.duration * 44100);  // Dur�e en �chantillons

        Uint8* buffer = new Uint8[toneLength];  // Allouer un buffer pour les donn�es audio
        generateTone(buffer, toneLength, frequency);  // G�n�rer la tonalit�

        // Mettre en file d'attente les donn�es audio pour la lecture
        SDL_QueueAudio(1, buffer, toneLength);

        // D�lai entre les notes (dur�e de la note en millisecondes)
        SDL_Delay(static_cast<int>(note.duration * 1000));

        delete[] buffer;  // Lib�rer le buffer apr�s utilisation
    }

    SDL_CloseAudio();  // Fermer le p�riph�rique audio
    SDL_Quit();  // Quitter SDL

    return 0;
}

int Partition::jouerStarWars() const {

    // D�finir une structure pour la note et sa dur�e
    struct Note {
        string note;
        float duration;
    };

    if (!initSDL()) {
        return 1;
    }

    // D�finir la m�lodie de StarWars
    vector<Note> melody = {
        {"A#1", 0.125}, {"0", 0.1625}, {"A#1", 0.125}, {"0", 0.1625}, {"A#1", 0.125}, {"0", 0.1625},
        {"F2", 0.25}, {"0", 0.325}, {"C2", 0.125}, {"0", 0.1625},
        {"A#2", 0.25}, {"0", 0.325}, {"A2", 0.25}, {"0", 0.325},
        {"G2", 0.125}, {"0", 0.1625}, {"F1", 0.0625}, {"0", 0.08125},
        {"C1", 0.25}, {"0", 0.325}, {"A#2", 0.25}, {"0", 0.325},
        {"A2", 0.25}, {"0", 0.325}, {"G2", 0.125}, {"0", 0.1625},
        {"F1", 0.0625}, {"0", 0.08125}, {"C1", 0.25}, {"0", 0.325},
        {"A#2", 0.25}, {"0", 0.325}, {"A2", 0.25}, {"0", 0.325},
        {"G2", 0.125}, {"0", 0.1625}, {"F1", 0.0625}, {"0", 0.08125},
        {"C1", 0.25}, {"0", 0.325}, {"A#2", 0.25}, {"0", 0.325},
        {"A2", 0.25}, {"0", 0.325}, {"A#2", 0.25}, {"0", 0.325},
        {"G2", 0.25}, {"0", 0.325}, {"C1", 0.25}, {"0", 0.325},
        {"C1", 0.25}, {"0", 0.325}, {"C1", 0.25}, {"0", 0.325},
        {"F2", 0.25}, {"0", 0.325}, {"C2", 0.125}, {"0", 0.1625},
        {"A#2", 0.25}, {"0", 0.325}, {"A2", 0.25}, {"0", 0.325},
        {"G2", 0.125}, {"0", 0.1625}, {"F1", 0.0625}, {"0", 0.08125},
        {"C1", 0.25}, {"0", 0.325}, {"A#2", 0.25}, {"0", 0.325},
        {"A2", 0.25}, {"0", 0.325}, {"G2", 0.125}, {"0", 0.1625},
        {"F1", 0.0625}, {"0", 0.08125}, {"C1", 0.25}, {"0", 0.325},
        {"A#2", 0.25}, {"0", 0.325}, {"A2", 0.25}, {"0", 0.325}
    };

    // Parcours de chaque note dans la m�lodie
    for (const auto& note : melody) {

        int frequency = noteToFrequency(note.note);  // Obtenir la fr�quence de la note
        int toneLength = static_cast<int>(note.duration * 44100);  // Dur�e en �chantillons

        Uint8* buffer = new Uint8[toneLength];  // Allouer un buffer pour les donn�es audio
        generateTone(buffer, toneLength, frequency);  // G�n�rer la tonalit�

        // Mettre en file d'attente les donn�es audio pour la lecture
        SDL_QueueAudio(1, buffer, toneLength);

        // D�lai entre les notes (dur�e de la note en millisecondes)
        SDL_Delay(static_cast<int>(note.duration * 1000));

        delete[] buffer;  // Lib�rer le buffer apr�s utilisation
    }

    SDL_CloseAudio();  // Fermer le p�riph�rique audio
    SDL_Quit();  // Quitter SDL

    return 0;
}

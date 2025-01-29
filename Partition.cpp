#include "Partition.hpp"
#include "Fonctions_audio.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int Partition::jouer() const {

    // Définir une structure pour la note et sa durée
    struct Note {
        std::string note;
        float duration;  // Durée en secondes
    };

    if (!initSDL()) {
        return 1;
    }

    // Définir la mélodie avec les notes et les durées adaptées au tempo du thème de Mario (120 BPM)
    std::vector<Note> melody = {
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

    // Parcours de chaque note dans la mélodie
    for (const auto& note : melody) {
        int frequency = noteToFrequency(note.note);  // Obtenir la fréquence de la note
        int toneLength = static_cast<int>(note.duration * 44100);  // Durée en échantillons

        Uint8* buffer = new Uint8[toneLength];  // Allouer un buffer pour les données audio
        generateTone(buffer, toneLength, frequency);  // Générer la tonalité

        // Mettre en file d'attente les données audio pour la lecture
        SDL_QueueAudio(1, buffer, toneLength);

        // Délai entre les notes (durée de la note en millisecondes)
        SDL_Delay(static_cast<int>(note.duration * 1000));  // Attendre la durée de la note

        delete[] buffer;  // Libérer le buffer après utilisation
    }

    SDL_Delay(5000);  // Attendre avant de fermer (laisser le temps à la dernière note de se jouer)

    SDL_CloseAudio();  // Fermer le périphérique audio
    SDL_Quit();  // Quitter SDL

    return 0;
}

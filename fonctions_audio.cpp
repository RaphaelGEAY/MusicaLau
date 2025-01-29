#include "Fonctions_audio.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

// Fonction pour charger les fichiers audio
Mix_Chunk* loadSound(const std::string& file) {
    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    if (!chunk) {
        std::cerr << "Erreur : Impossible de charger " << file << " - " << Mix_GetError() << std::endl;
    }
    return chunk;
}

// Fonction pour jouer une note
void playNote(const std::map<std::string, Mix_Chunk*>& notes, const std::string& key) {
    auto it = notes.find(key);
    if (it != notes.end() && it->second != nullptr) {
        std::cout << "Jouer la note : " << key << std::endl; // Ajoute ceci
        int channel = Mix_PlayChannel(-1, it->second, 0);
        if (channel == -1) {
            std::cerr << "Erreur lors de la lecture de la note : " << Mix_GetError() << std::endl;
        }
    }
    else {
        std::cerr << "Erreur : Note pour la touche '" << key << "' introuvable ou non chargée !" << std::endl;
    }
}

// Mapper les noms de notes aux fréquences
int noteToFrequency(const std::string& note) {
    if (note == "E7") return 2637;
    if (note == "C7") return 2093;
    if (note == "G7") return 3136;
    if (note == "A7") return 3520;
    if (note == "F7") return 2794;
    if (note == "G6") return 1568;
    if (note == "E6") return 1318;
    if (note == "A6") return 1760;
    if (note == "B6") return 1976;
    if (note == "A#6") return 1865;
    if (note == "D7") return 2349;
    return 0;  // Silence (pause)
}

// Générer un buffer de sinusoïde pour la fréquence donnée
void generateTone(Uint8* buffer, int length, int frequency, int sampleRate) {
    if (frequency == 0) {  // Pour une pause
        std::fill(buffer, buffer + length, 128);  // Silence
    }
    else {
        for (int i = 0; i < length; i++) {
            buffer[i] = 127 * sin(2 * M_PI * frequency * i / sampleRate) + 128;
        }
    }
}

// Fonction pour initialiser SDL pour l'audio
bool initSDL() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "L'initialisation de SDL a échoué ! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Spécification du format audio voulu
    SDL_AudioSpec wanted_spec;
    SDL_zero(wanted_spec);
    wanted_spec.freq = 44100;  // Fréquence d'échantillonnage
    wanted_spec.format = AUDIO_U8;  // Format de données audio (8 bits non signé)
    wanted_spec.channels = 1;  // Mono
    wanted_spec.samples = 4096;  // 1024 échantillons par callback

    // Ouvrir le périphérique audio avec les spécifications souhaitées
    if (SDL_OpenAudio(&wanted_spec, nullptr) < 0) {
        std::cerr << "SDL_OpenAudio a échoué ! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Démarrer immédiatement la lecture audio
    SDL_PauseAudio(0);
    return true;
}

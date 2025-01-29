#include "Fonctions_audio.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Fonction pour charger les fichiers audio
Mix_Chunk* loadSound(const string& file) {
    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    if (!chunk) {
        cerr << "Erreur : Impossible de charger " << file << " - " << Mix_GetError() << endl;
    }
    return chunk;
}

// Fonction pour jouer une note
void playNote(const map<string, Mix_Chunk*>& notes, const string& key) {
    auto it = notes.find(key);
    if (it != notes.end() && it->second != nullptr) {
        int channel = Mix_PlayChannel(-1, it->second, 0);
        if (channel == -1) {
            cerr << "Erreur lors de la lecture de la note : " << Mix_GetError() << endl;
        }
    }
}

map<string, int> note_to_frequency = {
    {"B0", 31}, {"C1", 33}, {"C#1", 35}, {"D1", 37}, {"D#1", 39}, {"E1", 41}, {"F1", 44}, {"F#1", 46}, {"G1", 49}, {"G#1", 52},
    {"A1", 55}, {"A#1", 58}, {"B1", 62}, {"C2", 65}, {"C#2", 69}, {"D2", 73}, {"D#2", 78}, {"E2", 82}, {"F2", 87}, {"F#2", 93},
    {"G2", 98}, {"G#2", 104}, {"A2", 110}, {"A#2", 117}, {"B2", 123}, {"C3", 131}, {"C#3", 139}, {"D3", 147}, {"D#3", 156},
    {"E3", 165}, {"F3", 175}, {"F#3", 185}, {"G3", 196}, {"G#3", 208}, {"A3", 220}, {"A#3", 233}, {"B3", 247}, {"C4", 262},
    {"C#4", 277}, {"D4", 294}, {"D#4", 311}, {"E4", 330}, {"F4", 349}, {"F#4", 370}, {"G4", 392}, {"G#4", 415}, {"A4", 440},
    {"A#4", 466}, {"B4", 494}, {"C5", 523}, {"C#5", 554}, {"D5", 587}, {"D#5", 622}, {"E5", 659}, {"F5", 698}, {"F#5", 740},
    {"G5", 784}, {"G#5", 831}, {"A5", 880}, {"A#5", 932}, {"B5", 988}, {"C6", 1047}, {"C#6", 1109}, {"D6", 1175}, {"D#6", 1245},
    {"E6", 1319}, {"F6", 1397}, {"F#6", 1480}, {"G6", 1568}, {"G#6", 1661}, {"A6", 1760}, {"A#6", 1865}, {"B6", 1976},
    {"C7", 2093}, {"C#7", 2217}, {"D7", 2349}, {"D#7", 2489}, {"E7", 2637}, {"F7", 2794}, {"F#7", 2960}, {"G7", 3136},
    {"G#7", 3322}, {"A7", 3520}, {"A#7", 3729}, {"B7", 3951}, {"C8", 4186}, {"C#8", 4435}, {"D8", 4699}, {"D#8", 4978}
};

// Fonction pour récupérer la fréquence d'une note
int noteToFrequency(const string& note) {
    auto it = note_to_frequency.find(note);
    if (it != note_to_frequency.end()) {
        return it->second;
    }
    return 0;
}

// Générer un buffer de sinusoïde pour la fréquence donnée
void generateTone(Uint8* buffer, int length, int frequency, int sampleRate) {
    if (frequency == 0) {
        fill(buffer, buffer + length, 128);
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
        cerr << "L'initialisation de SDL a échoué ! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    // Spécification du format audio voulu
    SDL_AudioSpec wanted_spec;
    SDL_zero(wanted_spec);
    wanted_spec.freq = 44100;
    wanted_spec.format = AUDIO_U8;
    wanted_spec.channels = 1;
    wanted_spec.samples = 4096;

    // Ouvrir le périphérique audio avec les spécifications souhaitées
    if (SDL_OpenAudio(&wanted_spec, nullptr) < 0) {
        cerr << "SDL_OpenAudio a échoué ! SDL_Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }

    // Démarrer immédiatement la lecture audio
    SDL_PauseAudio(0);
    return true;
}

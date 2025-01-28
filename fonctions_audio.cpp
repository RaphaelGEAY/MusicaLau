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

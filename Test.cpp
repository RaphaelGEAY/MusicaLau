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
        int channel = Mix_PlayChannel(-1, it->second, 0);
        if (channel == -1) {
            std::cerr << "Erreur lors de la lecture de la note : " << Mix_GetError() << std::endl;
        }
    }
    else {
        std::cerr << "Erreur : Note pour la touche '" << key << "' introuvable ou non chargée !" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "Erreur : Impossible d'initialiser SDL : " << SDL_GetError() << std::endl;
        return -1;
    }

    // Création d'une fenêtre pour capturer les événements clavier
    SDL_Window* window = SDL_CreateWindow("SDL Music Notes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Erreur : Impossible de créer la fenêtre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Initialisation de SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Erreur : Impossible d'initialiser SDL_mixer : " << Mix_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Chargement des sons
    std::map<std::string, Mix_Chunk*> notes;
    notes["A"] = loadSound("C:\\sounds\\C.wav");
    notes["Z"] = loadSound("C:\\sounds\\D.wav");
    notes["E"] = loadSound("C:\\sounds\\E.wav");
    notes["R"] = loadSound("C:\\sounds\\F.wav");
    notes["T"] = loadSound("C:\\sounds\\G.wav");
    notes["Y"] = loadSound("C:\\sounds\\A.wav");
    notes["U"] = loadSound("C:\\sounds\\B.wav");
    notes["I"] = loadSound("C:\\sounds\\C1.wav");

    // Vérification des fichiers chargés
    for (const auto& note : notes) {
        if (!note.second) {
            std::cerr << "Attention : Le fichier pour la touche '" << note.first << "' n'a pas été chargé correctement." << std::endl;
        }
    }

    // Mode interactif pour jouer des notes
    std::cout << "Appuyez sur les touches A, Z, E, R, T, Y, U, I pour jouer des notes. Appuyez sur Q pour quitter.\n";
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                std::string key = SDL_GetKeyName(event.key.keysym.sym);
                std::transform(key.begin(), key.end(), key.begin(), ::toupper);

                if (key == "Q") {
                    running = false;
                }
                else {
                    playNote(notes, key);
                }
            }
        }
    }

    // Libération des ressources
    for (auto& pair : notes) {
        Mix_FreeChunk(pair.second);
    }

    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

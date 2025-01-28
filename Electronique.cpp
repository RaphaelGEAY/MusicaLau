#include "Electronique.hpp"
#include "Fonctions_audio.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

Electronique::Electronique() : Instrument("Electronique") {}

void Electronique::jouerNote(const std::string& note) const {
    std::cout << "Piano joue : " << note << std::endl;
}

void Electronique::afficher() const {
    std::cout << "Instrument : " << nom << std::endl;
}

int Electronique::modeInteractif() const{
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "Erreur : Impossible d'initialiser SDL : " << SDL_GetError() << std::endl;
        return -1;
    }

    // Création d'une fenêtre pour capturer les événements clavier
    SDL_Window* window = SDL_CreateWindow("SDL Music Notes",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Erreur : Impossible de créer la fenêtre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Initialisation de SDL_mixer
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Erreur : Impossible d'initialiser SDL_mixer : " << Mix_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    if (Mix_AllocateChannels(128) < 0) {
        std::cerr << "Error allocating channels: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    // Chargement des sons
    std::map<std::string, Mix_Chunk*> notes;
    notes["<"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\C.wav");
    notes["Q"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\C#.wav");
    notes["W"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\D.wav");
    notes["S"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\D#.wav");
    notes["X"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\E.wav");
    notes["C"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\F.wav");
    notes["F"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\F#.wav");
    notes["V"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\G.wav");
    notes["G"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\G#.wav");
    notes["B"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\A.wav");
    notes["H"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\A#.wav");
    notes["N"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\B.wav");
    notes[","] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\C2.wav");
    notes["K"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\C#2.wav");
    notes[";"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\D2.wav");
    notes["L"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\D#2.wav");
    notes[":"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\E2.wav");
    notes["!"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\F2.wav");
    notes["*"] = loadSound("C:\\Users\\rapha\\Documents\\Ynov\\MusicaLau\\Piano\\F#2.wav");

    // Vérification des fichiers chargés
    for (const auto& note : notes) {
        if (!note.second) {
            std::cerr << "Attention : Le fichier pour la touche '" << note.first << "' n'a pas été chargé correctement." << std::endl;
        }
    }

    // Mode interactif pour jouer des notes
    std::cout << "Appuyez sur les touches du clavier pour jouer des notes. Appuyez sur P pour quitter.\n";
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            // Vérification des événements de fenêtre
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                    std::cout << "La fenêtre a gagné le focus." << std::endl;
                }
                else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                    std::cout << "La fenêtre a perdu le focus." << std::endl;
                }
            }

            // Gestion des autres événements
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                std::string key = SDL_GetKeyName(event.key.keysym.sym);
                std::transform(key.begin(), key.end(), key.begin(), ::toupper);

                if (key == "P") {
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

#include "Guitare.hpp"
#include "Fonctions_audio.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

Guitare::Guitare() : Instrument("Guitare") {}

void Guitare::jouerNote(const std::string& note) const {
    std::cout << "Guitare joue : " << note << std::endl;
}

void Guitare::afficher() const {
    std::cout << "Instrument : " << nom << std::endl;
}

int Guitare::modeInteractif() const{
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "Erreur : Impossible d'initialiser SDL : " << SDL_GetError() << std::endl;
        return -1;
    }

    // Cr�ation d'une fen�tre pour capturer les �v�nements clavier
    SDL_Window* window = SDL_CreateWindow("SDL Music Notes",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Erreur : Impossible de cr�er la fen�tre : " << SDL_GetError() << std::endl;
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
    notes["<"] = loadSound("C:\\Instruments\\Guitare\\C.wav");
    notes["Q"] = loadSound("C:\\Instruments\\Guitare\\C#.wav");
    notes["W"] = loadSound("C:\\Instruments\\Guitare\\D.wav");
    notes["S"] = loadSound("C:\\Instruments\\Guitare\\D#.wav");
    notes["X"] = loadSound("C:\\Instruments\\Guitare\\E.wav");
    notes["C"] = loadSound("C:\\Instruments\\Guitare\\F.wav");
    notes["F"] = loadSound("C:\\Instruments\\Guitare\\F#.wav");
    notes["V"] = loadSound("C:\\Instruments\\Guitare\\G.wav");
    notes["G"] = loadSound("C:\\Instruments\\Guitare\\G#.wav");
    notes["B"] = loadSound("C:\\Instruments\\Guitare\\A.wav");
    notes["H"] = loadSound("C:\\Instruments\\Guitare\\A#.wav");
    notes["N"] = loadSound("C:\\Instruments\\Guitare\\B.wav");
    notes[","] = loadSound("C:\\Instruments\\Guitare\\C2.wav");
    notes["K"] = loadSound("C:\\Instruments\\Guitare\\C#2.wav");
    notes[";"] = loadSound("C:\\Instruments\\Guitare\\D2.wav");
    notes["L"] = loadSound("C:\\Instruments\\Guitare\\D#2.wav");
    notes[":"] = loadSound("C:\\Instruments\\Guitare\\E2.wav");
    notes["!"] = loadSound("C:\\Instruments\\Guitare\\F2.wav");
    notes["*"] = loadSound("C:\\Instruments\\Guitare\\F#2.wav");

    // V�rification des fichiers charg�s
    for (const auto& note : notes) {
        if (!note.second) {
            std::cerr << "Attention : Le fichier pour la touche '" << note.first << "' n'a pas �t� charg� correctement." << std::endl;
        }
    }

    // Mode interactif pour jouer des notes
    std::cout << "Appuyez sur les touches du clavier pour jouer des notes. Appuyez sur P pour quitter.\n";
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            // V�rification des �v�nements de fen�tre
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                    std::cout << "La fen�tre a gagn� le focus." << std::endl;
                }
                else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                    std::cout << "La fen�tre a perdu le focus." << std::endl;
                }
            }

            // Gestion des autres �v�nements
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

    // Lib�ration des ressources
    for (auto& pair : notes) {
        Mix_FreeChunk(pair.second);
    }

    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

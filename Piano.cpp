#include "Piano.hpp"
#include "Fonctions_audio.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

Piano::Piano() : Instrument("Piano") {}

int Piano::modeInteractif() const{

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        cerr << "Erreur : Impossible d'initialiser SDL : " << SDL_GetError() << endl;
        return -1;
    }

    // Création d'une fenêtre pour capturer les événements clavier
    SDL_Window* window = SDL_CreateWindow("SDL Music Notes",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    if (!window) {
        cerr << "Erreur : Impossible de creer la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    // Initialisation de SDL_mixer
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "Erreur : Impossible d'initialiser SDL_mixer : " << Mix_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Alocation des canaux de mixage
    if (Mix_AllocateChannels(128) < 0) {
        cerr << "Erreur d'allocation des canaux de mixage: " << Mix_GetError() << endl;
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    // Chargement des sons
    map<string, Mix_Chunk*> notes;
    notes["<"] = loadSound("Instruments\\Piano\\C.wav");
    notes["Q"] = loadSound("Instruments\\Piano\\C#.wav");
    notes["W"] = loadSound("Instruments\\Piano\\D.wav");
    notes["S"] = loadSound("Instruments\\Piano\\D#.wav");
    notes["X"] = loadSound("Instruments\\Piano\\E.wav");
    notes["C"] = loadSound("Instruments\\Piano\\F.wav");
    notes["F"] = loadSound("Instruments\\Piano\\F#.wav");
    notes["V"] = loadSound("Instruments\\Piano\\G.wav");
    notes["G"] = loadSound("Instruments\\Piano\\G#.wav");
    notes["B"] = loadSound("Instruments\\Piano\\A.wav");
    notes["H"] = loadSound("Instruments\\Piano\\A#.wav");
    notes["N"] = loadSound("Instruments\\Piano\\B.wav");
    notes[","] = loadSound("Instruments\\Piano\\C2.wav");
    notes["K"] = loadSound("Instruments\\Piano\\C#2.wav");
    notes[";"] = loadSound("Instruments\\Piano\\D2.wav");
    notes["L"] = loadSound("Instruments\\Piano\\D#2.wav");
    notes[":"] = loadSound("Instruments\\Piano\\E2.wav");
    notes["!"] = loadSound("Instruments\\Piano\\F2.wav");
    notes["*"] = loadSound("Instruments\\Piano\\F#2.wav");

    // Vérification des fichiers chargés
    for (const auto& note : notes) {
        if (!note.second) {
            cerr << "Attention : Le fichier pour la touche : " << note.first << " n'a pas ete charge correctement" << endl;
        }
    }

    // Mode interactif pour jouer des notes
    bool running = true;
    SDL_Event event;

    while (running) {

        while (SDL_PollEvent(&event)) {

            // Vérification des événements de fenêtre
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                    cout << "Window +" << endl;
                }
                else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                    cout << "Window -" << endl;
                }
            }

            // Gestion des autres événements
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {

                string key = SDL_GetKeyName(event.key.keysym.sym);
                transform(key.begin(), key.end(), key.begin(), ::toupper);

                if (key == "R") {
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

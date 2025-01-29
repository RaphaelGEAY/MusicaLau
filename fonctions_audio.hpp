#ifndef FONCTIONS_AUDIO_HPP
#define FONCTIONS_AUDIO_HPP

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <map>

using namespace std;

Mix_Chunk* loadSound(const string& file);
void playNote(const map<string, Mix_Chunk*>& notes, const string& key);
int noteToFrequency(const string& note);
void generateTone(Uint8* buffer, int length, int frequency, int sampleRate = 44100);
bool initSDL();

#endif

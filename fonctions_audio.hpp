#ifndef FONCTIONS_AUDIO_HPP
#define FONCTIONS_AUDIO_HPP

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <map>

Mix_Chunk* loadSound(const std::string& file);
void playNote(const std::map<std::string, Mix_Chunk*>& notes, const std::string& key);
int noteToFrequency(const std::string& note);
void generateTone(Uint8* buffer, int length, int frequency, int sampleRate = 44100);
bool initSDL();

#endif

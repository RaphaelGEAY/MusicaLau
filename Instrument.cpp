#include "Instrument.hpp"

using namespace std;

Instrument::Instrument(const string nomInstrument) : nom(nomInstrument) {}

int Instrument::modeInteractif() const {
    return 0;
}

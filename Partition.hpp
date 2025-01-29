#ifndef PARTITION_HPP
#define PARTITION_HPP

#include "Instrument.hpp"

#include <vector>
#include <string>

using namespace std;

class Partition {
private:
    vector<string> notes;
public:
    int jouerMario() const;
    int jouerStarWars() const;
};

#endif

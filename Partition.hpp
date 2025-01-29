#ifndef PARTITION_HPP
#define PARTITION_HPP

#include <vector>
#include <string>
#include "Instrument.hpp"

class Partition {
private:
    std::vector<std::string> notes;
public:
    void chargerPartition(const std::string& nomFichier);
    void jouer(const Instrument& instrument, const std::string& rythme) const;
};

#endif

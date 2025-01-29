#ifndef PARTITION_HPP
#define PARTITION_HPP

#include <vector>
#include <string>
#include "Instrument.hpp"

class Partition {
private:
    std::vector<std::string> notes;
public:
    int jouer() const;
};

#endif

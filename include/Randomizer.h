#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>

#include "Grapher.h"

constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_MAX = 1;

class Randomizer {
private:
    std::vector<float> classes;
    int maxClass;

public:
    Randomizer() = default;
    Randomizer(std::vector<float> classes);

    int random();
    int graphicRandom();
};

#endif // RANDOMIZER_H
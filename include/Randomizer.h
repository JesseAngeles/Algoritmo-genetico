#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>

class Randomizer
{
private:
    std::random_device rd; // Dispositivo aleatorio para la semilla
    std::mt19937 engine;   // Motor de generación aleatoria (Mersenne Twister)

public:
    Randomizer();
    float generate(float min, float max);

    // Getters
    std::mt19937 &getEngine() { return engine; }
};

#endif // RANDOMIZER_H
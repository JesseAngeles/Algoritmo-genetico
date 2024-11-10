#include "Randomizer.h"

Randomizer::Randomizer()
    : engine(rd()) {}

float Randomizer::generate(float min, float max)
{
    std::uniform_real_distribution<float> distribution(min, max);
    
    return distribution(engine);
}

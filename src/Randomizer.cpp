#include "Randomizer.h"

float random(float min, float max)
{
    std::random_device rd;                 
    std::mt19937 gen(rd());                  
    std::uniform_real_distribution<float> distr(min, max); 

    return distr(gen);
}
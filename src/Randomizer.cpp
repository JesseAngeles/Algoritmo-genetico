#include "Randomizer.h"

Randomizer::Randomizer(std::vector<float> classes) : classes(classes)
{
    this->maxClass = this->classes.size();

    std::srand(std::time(nullptr));
};

int Randomizer::random()
{
    float random_num = FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX / (FLOAT_MAX - FLOAT_MIN)));

    for (int i = 0; i < classes.size(); i++)
        if (random_num <= classes[i])
            return i;

    return 1;
}

int Randomizer::graphicRandom()
{
    
    Grapher grapher;

    for (const auto &cls : classes)
        grapher.drawDivisor(cls * 2 * M_PI);

    return grapher.draw(rand() % 5 + 1);
}

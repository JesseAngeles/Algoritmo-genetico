#include "Randomizer.h"

Randomizer::Randomizer(std::vector<float> classes) : classes(classes)
{
    this->maxClass = this->classes.size();

    // std::srand(std::time(nullptr));
};

int Randomizer::random()
{
    std::random_device rd;                  // Generador basado en hardware
    std::mt19937 gen(rd());                  
    std::uniform_real_distribution<float> distr(FLOAT_MIN, FLOAT_MAX); // Distribución uniforme

    float random_num = distr(gen);          // Generar un número aleatorio en el rango [FLOAT_MIN, FLOAT_MAX]
    for (int i = 0; i < classes.size(); i++)
        if (random_num <= classes[i])
            return i;                        

    return 1;                           
}

int Randomizer::graphicRandom()
{
    Grapher grapher;

    float count = 0;

    for (const auto &cls : classes)
    {
        grapher.drawDivisor(cls * 2 * M_PI, cls - count);
        count = cls;
    }

    std::random_device rd;                        
    std::mt19937 gen(rd());                   
    std::uniform_int_distribution<int> distr(1, 5);  

    return grapher.draw(distr(gen));
}
#ifndef GENERATION_H
#define GENERATION_H

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>


#include <iostream>

#include "Randomizer.h"
#include "Grapher.h"

#define MAX_PROBABILITY_MUTATION 0.5
#define MAX_NO_IMPROVEMENT 100

class Generation
{
private:
    // Configuration
    int min;
    int max;

    int size;
    int generation_count;

    // Attributes
    std::vector<int> population;
    std::vector<int> max_population;
    float probabilty_mutation;

    // Genetic
    long (*fitness)(int);
    void (*selection)(std::vector<int> &population, const std::vector<long> &fitnesses);
    void (*crossover)(std::pair<int, int> &);
    void (*mutation)(int &);

    // Classes
    Randomizer randomizer;

    // Functions
    void evolvePopulation();
    bool isEndogamicPopulation(std::vector<int> population);
    bool isMaximized();
    long ratePopulation(std::vector<int> population);

public:
    // Constructor
    Generation(std::vector<int> population, int min, int max, float probabilty_mutation,
               long (*fitness)(int),
               void (*selection)(std::vector<int> &, const std::vector<long> &),
               void (*crossover)(std::pair<int, int> &),
               void (*mutation)(int &));

    // Functions
    int start(bool printPopulation);

    // Getters
    int getGenerationCount() const { return generation_count; }
    std::vector<int> getPopulation() const { return population; }
    std::vector<int> getMaxPopulation() const { return max_population; }

    // Setters
    void setPopulation(std::vector<int> population) { this->population = population; }

    // Print
    void printPopulation(std::vector<int>);
};

#endif // GENERATION_H
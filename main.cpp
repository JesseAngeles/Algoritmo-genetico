#include <iostream>
#include <vector>
#include <set>

#include "Generation.h"
#include "Randomizer.h"

#include "./src/functions/FitnessFunctions.cpp"
#include "./src/functions/CrossoverFunctions.cpp"
#include "./src/functions/MutationFunctions.cpp"
#include "./src/functions/SelectionFunctions.cpp"

using namespace std;

std::vector<int> createInitPopulation(int size, int min, int max);

int main()
{
    int size = 10;
    int min = 0;
    int max = 100000;
    float probabily_mutation = 0.01;

    for (int i = 0; i < 5; ++i) {
        std::vector<int> initPopulation = createInitPopulation(size, min, max);
        // std::vector<int> initPopulation = {13, 24, 8, 19};

        Generation generation(initPopulation,
                              min, max, probabily_mutation,
                              functionSquare,
                              rankSelection,
                              singlePointCrossover,
                              pointMutation);

        std::cout << "Iteración " << (i + 1) << ":\n";
        
        std::cout << "Población Inicial:";
        generation.printPopulation(generation.getPopulation());

        int error_data = generation.start(false);
        
        std::cout << "Ajustes: " << error_data << "\n";
        std::cout << "Total: " << generation.getGenerationCount() << "\n";
        
        std::cout << "Población Final:";
        generation.printPopulation(generation.getPopulation());
        
        std::cout << "Mejor Población:";
        generation.printPopulation(generation.getMaxPopulation());

        std::cout << "----------------------------------------\n";
    }

    return 0;
}


std::vector<int> createInitPopulation(int size, int min, int max)
{
    Randomizer randomizer;
    std::vector<int> population;

    population.reserve(size);

    for (int i = 0; i < size; i++)
        population.push_back(std::round(randomizer.generate(min, max)));

    return population;
}
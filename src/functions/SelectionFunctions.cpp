#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

#include <iostream>

#include "Randomizer.h"
#include "Binary.h"
#include "Grapher.h"

void rouletteWheelSelection(std::vector<int> &population, const std::vector<long> &fitnesses)
{
    // Randomizador
    Randomizer randomizer;

    // Calcular la aptitud total
    float total_fitness = 0;
    for (long fitness : fitnesses)
        total_fitness += fitness;
    // Calcular probabilidad de seleccion
    std::vector<float> probabilities;
    probabilities.reserve(fitnesses.size());

    for (long fitness : fitnesses)
        probabilities.push_back(fitness / total_fitness);

    // Calcular probabilidad acumulada
    float sum = 0;
    for (float &prob : probabilities)
    {
        sum += prob;
        prob = sum;
    }

    // Seleccion
    std::vector<int> new_population;

    for (int i = 0; i < population.size(); i++)
    {
        float random_number = randomizer.generate(0, 1);
        for (int j = 0; j < probabilities.size(); j++)
            if (random_number <= probabilities[j])
            {
                new_population.push_back(population[j]);
                break;
            }
    }

    // Reasignacion
    population = new_population;
}

void rouletteWheelSelectionAnimated(std::vector<int> &population, const std::vector<long> &fitnesses)
{
    // Randomizador
    Randomizer randomizer;

    // Calcular la aptitud total
    float total_fitness = 0;
    for (long fitness : fitnesses)
        total_fitness += fitness;
    // Calcular probabilidad de seleccion
    std::vector<float> probabilities;
    probabilities.reserve(fitnesses.size());

    for (long fitness : fitnesses)
        probabilities.push_back(fitness / total_fitness);

    // Calcular probabilidad acumulada
    float sum = 0;
    for (float &prob : probabilities)
    {
        sum += prob;
        prob = sum;
    }

    // Seleccion
    std::vector<int> new_population;

    for (int i = 0; i < population.size(); i++)
    {
        float random_number = randomizer.generate(2, 5);
        
        Grapher grapher;
        for (int i = 0; i < population.size(); i++)
            grapher.drawDivisor(probabilities[i] * 2 * M_PI, population[i]);
        int index = grapher.draw(random_number);

        for (int j = 0; j < probabilities.size(); j++)
            if (random_number <= probabilities[j])
            {
                new_population.push_back(population[j]);
                break;
            }
    }

    // Reasignacion
    population = new_population;
}

void tournamentSelection(std::vector<int> &population, const std::vector<long> &fitnesses)
{
    // Randomizador
    Randomizer randomizer;

    std::vector<int> new_population;

    for (int i = 0; i < population.size(); i++)
    {
        // Seleccion
        int first_pos = std::round(randomizer.generate(0, population.size() - 1));
        int second_pos;
        do
        {
            second_pos = std::round(randomizer.generate(0, population.size() - 1));
        } while (first_pos == second_pos);

        // Torneo
        new_population.push_back(population[(
            fitnesses[first_pos] >= fitnesses[second_pos]
                ? first_pos
                : second_pos)]);
    }

    // Reasignacion
    population = new_population;
}

void rankSelection(std::vector<int> &population, const std::vector<long> &fitnesses)
{
    // Randomizador
    Randomizer randomizer;

    // Ordenamiento
    std::vector<int> indexes(fitnesses.size());
    std::iota(indexes.begin(), indexes.end(), 0);

    std::sort(indexes.begin(), indexes.end(), [&fitnesses](int i1, int i2)
              {
                  return fitnesses[i1] > fitnesses[i2];
              });

    // Clasificación
    float total_ranking = population.size() * (population.size() + 1) / 2.0f;

    // Calcular probabilidad de selección
    std::vector<float> probabilities;
    probabilities.reserve(indexes.size());

    for (int i = 0; i < indexes.size(); ++i)
        probabilities.push_back((i + 1) / total_ranking);

    // Calcular probabilidad acumulada
    float sum = 0;
    for (float &prob : probabilities)
    {
        sum += prob;
        prob = sum;
    }

    // Selección
    std::vector<int> new_population;
    new_population.reserve(population.size());

    for (int i = 0; i < population.size(); i++)
    {
        float random_number = randomizer.generate(0, 1);
        for (int j = 0; j < probabilities.size(); j++)
        {
            if (random_number <= probabilities[j])
            {
                new_population.push_back(population[indexes[j]]);
                break;
            }
        }
    }

    // Reasignación
    population = new_population;
}

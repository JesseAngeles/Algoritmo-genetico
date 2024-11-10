#include "Generation.h"

// Constructor
Generation::Generation(std::vector<int> population, int min, int max, float probabilty_mutation,
                       long (*fitness)(int),
                       void (*selection)(std::vector<int> &, const std::vector<long> &),
                       void (*crossover)(std::pair<int, int> &),
                       void (*mutation)(int &))
    : population(population), min(min), max(max), probabilty_mutation(probabilty_mutation),
      fitness(fitness), selection(selection),
      crossover(crossover), mutation(mutation),
      size(population.size()), generation_count(0),
      randomizer() {}

void Generation::evolvePopulation()
{
    // Calcular las aptitudes
    std::vector<long> fitnesses;
    fitnesses.reserve(population.size());

    for (int organism : population)
        fitnesses.push_back(fitness(organism));

    // Seleccionar los padres
    selection(population, fitnesses);
    std::shuffle(population.begin(), population.end(), randomizer.getEngine());

    // Cruza
    std::vector<int> new_population;
    new_population.reserve(population.size());

    for (int i = 0; i < population.size(); i++)
    {
        std::pair<int, int> descendants = std::make_pair(
            population[i], population[++i]);

        crossover(descendants);

        new_population.push_back(descendants.first);
        new_population.push_back(descendants.second);
    }

    // Mutacion
    for (int &organism : new_population)
    {
        if (randomizer.generate(0, 1) <= probabilty_mutation)
            mutation(organism);

        // Corrective mutation
        while (organism < min || organism > max)
            mutation(organism);
    }

    // Reasignacion
    population = new_population;
}

bool Generation::isEndogamicPopulation(std::vector<int> population)
{
    int default_organism = population[0];
    for (const int &organism : population)
        if (default_organism != organism)
            return false;

    return true;
}

bool Generation::isMaximized()
{
    if (population[0] == max && isEndogamicPopulation(population))
        return true;

    return false;
}

long Generation::ratePopulation(std::vector<int> population)
{
    long total = 0;
    for (int organism : population)
        total += organism;

    return total; // static_cast<double>(total) / population.size();
}

int Generation::start(bool printPoblation)
{
    float init_probability = probabilty_mutation;
    int worst_count = 0;
    int no_improvement_count = 0;

    max_population = population;
    int rate_max = ratePopulation(max_population) * 1.05;

    do
    {
        if (isMaximized())
        {
            max_population = population;
            break;
        }
        if (probabilty_mutation > MAX_PROBABILITY_MUTATION)
            probabilty_mutation = MAX_PROBABILITY_MUTATION;

        // Guardar la población actual
        std::vector<int> previous_population = population;

        // Evolucionar la población
        evolvePopulation();

        // Actualizar probabilidad de mutación
        if (isEndogamicPopulation(population))
        {
            worst_count++;
            probabilty_mutation = std::min((float)MAX_PROBABILITY_MUTATION, probabilty_mutation * 2);
            generation_count--;
            no_improvement_count++;
            continue;
        }
        else if (isEndogamicPopulation(previous_population))
            probabilty_mutation /= 2;
        else
            probabilty_mutation = init_probability;

        // Evaluar la calidad
        int rate_previous = ratePopulation(previous_population);
        int rate_current = ratePopulation(population) * 1.05;

        // Si la nueva población no mejora
        if (rate_previous >= rate_current)
        {
            worst_count++;
            probabilty_mutation = std::min(1.0f, probabilty_mutation * 2);
            generation_count--;
            no_improvement_count++;
            continue;
        }
        else
        {
            if (rate_current > rate_max)
            {
                max_population = population;
                rate_max = rate_current;
            }
            no_improvement_count = 0; // Reiniciar contador si hay mejora
        }

        if (printPoblation)
            printPopulation(population);

    } while (++generation_count < 100000 && no_improvement_count < MAX_NO_IMPROVEMENT);

    probabilty_mutation = init_probability;

    return worst_count;
}

void Generation::printPopulation(std::vector<int> population)
{
    std::cout << std::endl;
    for (const int &organism : population)
        std::cout << organism << " ";
}
#include <iostream>
#include <bitset>
#include <cmath>

#include "FunctionGenetic.h"
#include "Randomizer.h"

#define BIT_SIZE 20

std::vector<int> mutationRandomBit(std::vector<int> values, int min, int max)
{
    int max_bit = std::ceil(std::log2(++max));

    int random_start = random(1, values.size());

    for (int i = random_start; i < values.size(); i++)
    {
        std::bitset<BIT_SIZE> binary(values[i]);

        int pos = random(0, max_bit);
        binary[pos] = !binary[pos];

        values[i] = int(binary.to_ulong()) % max;
    }

    return values;
}

std::vector<int> mutationMultipleRandom(std::vector<int> values, int min, int max)
{
    int max_bit = std::ceil(std::log2(++max));

    
    int random_start = random(1, values.size());

    for (int i = random_start; i < values.size(); i++)
    {
        std::bitset<BIT_SIZE> binary(values[i]);
        std::set<int> positions;
        int random_changes = random(0, max_bit);

        while (positions.size() != 5)
            positions.insert(random(0, max_bit));

        for (const int &pos : positions)
            binary[pos] = !binary[pos];

        values[i] = int(binary.to_ulong()) % max;
    }

    return values;
}
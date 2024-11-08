#include <iostream>
#include <cmath>
#include <bitset>

#include "FunctionGenetic.h"
#include "Randomizer.h"

#define BIT_SIZE 16

// El mejor gen crea parejas con mejores genes
std::vector<int> crossBestSwitchPair(std::vector<int> values, int min, int max)
{
    int max_bit = std::ceil(std::log2(max++));

    std::bitset<BIT_SIZE> min_2(min);
    std::bitset<BIT_SIZE> max_2(max);
    std::bitset<BIT_SIZE> best_value(values[0]);

    std::vector<int> new_values;

    for (int i = 1; i < values.size(); i++)
    {
        std::bitset<BIT_SIZE> best = best_value;
        std::bitset<BIT_SIZE> value(values[i]);
        const int num_bits = random(0, max_bit);

        for (int j = 0; j < num_bits; j++)
        {
            bool tmp = value[j];
            value[j] = best[j];
            best[j] = tmp;
        }

        new_values.push_back(int(best.to_ullong()) % max);
        if (new_values.size() == values.size())
            break;

        new_values.push_back(int(value.to_ullong()) % max);
        if (new_values.size() == values.size())
            break;
    }

    return new_values;
}

// El mejor gen hereda los genes de mayor valor a un solo hijo con los segundos mejores
std::vector<int> crossBestSwitch(std::vector<int> values, int min, int max)
{
    int max_bit = std::ceil(std::log2(++max));

    std::bitset<BIT_SIZE> min_2(min);
    std::bitset<BIT_SIZE> max_2(max);
    std::bitset<BIT_SIZE> best_value(values[0]);

    std::vector<int> new_values;
    new_values.push_back(values[0]);

    for (int i = 1; i < values.size(); i++)
    {
        std::bitset<BIT_SIZE> value(values[i]);
        const int num_bits = random(0, max_bit);

        for (int j = num_bits; j > 0; j--)
        {
            value[j] = best_value[j];
        }

        new_values.push_back(int(value.to_ullong()) % max);
        if (new_values.size() == values.size())
            break;
    }

    return new_values;
}
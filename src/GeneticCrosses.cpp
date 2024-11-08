#include <iostream>
#include <cmath>
#include <bitset>

#include "FunctionGenetic.h"
#include "Randomizer.h"

#define BIT_SIZE 16

std::vector<int> crossBinarySwitch(std::vector<int> values, int min, int max)
{
    int max_bit = std::ceil(std::log2(max));

    std::bitset<BIT_SIZE> min_2(min);
    std::bitset<BIT_SIZE> max_2(max);
    std::bitset<BIT_SIZE> best_value(values[0]);

    std::vector<int> new_values;

    // std::cout << "max_bit: " << max_bit << std::endl;
    // std::cout << "min: " << min << ": " << min_2 << std::endl;
    // std::cout << "max: " << max << ": " << max_2 << std::endl;
    // std::cout << "best: " << values[0] << ": " << best_value << std::endl;

    for (int i = 1; i < values.size(); i++)
    {
        std::bitset<BIT_SIZE> best = best_value;
        std::bitset<BIT_SIZE> value(values[i]);
        const int num_bits = random(0, max_bit);

        // std::cout << "num_bits: " << num_bits << std::endl;
        // std::cout << "value: " << values[i] << ": " << value << std::endl;

        for (int j = 0; j < num_bits; j++)
        {
            bool tmp = value[j];
            value[j] = best[j];
            best[j] = tmp;
        }

        new_values.push_back(int(best.to_ullong()));
        if (new_values.size() == values.size())
            break;

        new_values.push_back(int(value.to_ullong()));
        if (new_values.size() == values.size())
            break;
    }

    return new_values;
}

std::vector<int> geneticCrossBinarySwitch(std::vector<int> values, int min, int max)
{
    std::bitset<5> bestValue(values[0]);

    std::vector<int> newValues;

    for (int i = 1; i < values.size(); i++)
    {
        const int numBits = (2 * i) - 1;
        std::bitset<5> binary(values[i]);

        std::bitset<5> best = bestValue;
        // swap de valores binarios
        for (int j = 0; j < numBits; j++)
        {
            bool value = binary[j];
            binary[j] = best[j];
            best[j] = value;
        }

        newValues.push_back(int(best.to_ulong()) % 32);
        if (newValues.size() == values.size())
            break;

        newValues.push_back(int(binary.to_ulong()) % 32);
        if (newValues.size() == values.size())
            break;
    }

    return newValues;
}
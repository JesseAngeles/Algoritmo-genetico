#include <iostream>
#include <bitset>

#include "FunctionGenetic.h"

std::vector<int> geneticCrossBinarySwitch(std::vector<int> values)
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

std::vector<int> geneticCrossBinaryAddition(std::vector<int> values)
{
    return values;
}


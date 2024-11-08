#include <iostream>
#include <bitset>
#include <cmath>

#include "FunctionGenetic.h"
#include "Randomizer.h"

#define BIT_SIZE 16

std::vector<int> geneticMutationRandomSwitch(std::vector<int> values, int min, int max)
{
    int max_bit = std::ceil(std::log2(max));

    for (int i = values.size() / random(0, values.size()); i < values.size(); i++)
    {
        std::bitset<BIT_SIZE> binary(values[i]);

        int pos = random(0, max_bit);
        binary[pos] = !binary[pos];

        values[i] = int(binary.to_ulong());
    }

    return values;
}

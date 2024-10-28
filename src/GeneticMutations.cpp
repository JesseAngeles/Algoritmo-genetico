#include <iostream>
#include <bitset>

#include "FunctionGenetic.h"

std::vector<int> geneticMutationRandomSwitch(std::vector<int> values)
{
    for (int i = values.size() / 2; i < values.size(); i++)
    {
        std::bitset<5> binary(values[i]);

        int pos = rand() % 5;
        binary[pos] = !binary[pos];

        values[i] = int(binary.to_ulong());
    }

    return values;
}

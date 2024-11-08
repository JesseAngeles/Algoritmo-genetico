#ifndef FUNCTION_GENETIC_H
#define FUNCTION_GENETIC_H

#include <iostream>
#include <vector>

struct functionGenetic
{
    std::string name;
    std::vector<int> (*func) (std::vector<int>, int min, int max);
};

#endif // FUNCTION_GENETIC_H
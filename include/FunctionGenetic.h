#ifndef FUNCTION_GENETIC_H
#define FUNCTION_GENETIC_H

#include <iostream>
#include <vector>

struct functionGenetic
{
    std::string name;
    std::vector<int> (*func) (std::vector<int>);
};

#endif // FUNCTION_GENETIC_H
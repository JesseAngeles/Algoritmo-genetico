#include <iostream>

#include <cmath>

struct functionEntry
{
    std::string name;
    int (*func)(long int);
};

long functionSquare(int x) { return std::pow(x, 2); }
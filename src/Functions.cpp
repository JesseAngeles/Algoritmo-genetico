#include <iostream>

#include <cmath>

struct functionEntry
{
    std::string name;
    long int (*func)(long int);
};

long int functionSquare(long int x) { return x * x; }

long int functionCube(long int x) { return x * x * x; }

long int functionDoble(long int x) { return 2 * x; }

long int functionSin(long int x) { return 100 * sin(x); }

long int functionLog(long int x) { return 100 * log(x); }
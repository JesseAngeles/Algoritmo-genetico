#include <iostream>

#include <cmath>

struct functionEntry
{
    std::string name;
    int (*func)(int);
};

int functionSquare(int x) { return x * x; }

int functionCube(int x) { return x * x * x; }

int functionDoble(int x) { return 2 * x; }

int functionSin(int x) { return 100 * sin(x); }

int functionLog(int x) { return 100 * log(x); }
#include <iostream>

struct functionEntry
{
    std::string name;
    int (*func)(int);
};

int functionSquare(int x) { return x * x; }

int functionCube(int x) { return x * x * x; }

int functionDoble(int x) { return 2 * x; }
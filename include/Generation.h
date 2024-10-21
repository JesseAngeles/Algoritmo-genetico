#ifndef GENERATION_H
#define GENERATION_H

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

#include "Randomizer.h"

#define MIN 0
#define MAX 31

#define COUNT 10000

struct element
{
    int value;
    float expectedCount;
    int currentCount;
};

class Generation
{
private:
    int size;
    std::vector<element> elements;

    std::mutex countMutex;

    int (*function)(int);
    int functionTotal;
    float functionAverage;

    Randomizer randomizer;

    void calculateAverage();
    void calculateExpectedCount();
    void calculateCurrentCount();
    std::vector<float> calculateComulativeCount();
    void insertCurrentCount();
    void orderElements();

    // validaciones
    bool inRange(int);
    static bool compareByCurrentCount(const element &a, const element &b);

public:
    // Constructor
    Generation(std::vector<int>, int (*)(int));

    // getters
    std::vector<element> getElements() const { return this->elements; }

    // setters

    // impresiones
    void printElements();
};

#endif // GENERATION_H
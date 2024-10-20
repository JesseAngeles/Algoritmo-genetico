#ifndef GENERATION_H
#define GENERATION_H

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

#include "Randomizer.h"

#define MIN 0
#define MAX 31

#define COUNT 1

class Generation
{
private:
    int size;
    std::vector<int> values;
    std::vector<float> expectedCount;
    std::vector<int> currentCount;

    std::mutex countMutex;

    int (*function)(int);
    int functionTotal;
    float functionAverage;

    Randomizer randomizer;

    void calculateAverage();
    void calculateExpectedCount();
    std::vector<float> calculateComulativeCount();

    void insertCurrentCount();

    // validaciones
    bool inRange(int);

public:
    // Constructor
    Generation(std::vector<int>, int (*)(int));

    // getters
    std::vector<int> getValues() const { return values; }

    // setters
    void setValues(std::vector<int> values) { this->values = values; }

    // impresiones
    void print();
};

#endif // GENERATION_H
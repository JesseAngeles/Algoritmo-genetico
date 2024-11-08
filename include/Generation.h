#ifndef GENERATION_H
#define GENERATION_H

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <atomic>

#include "Randomizer.h"
#include "Grapher.h"

#define TESTS 50000

struct element
{
    int value;
    float expectedCount;
    float cumulativeExpectedCount;
    int currentCount;
};

class Generation
{
private:
    int size;
    int min;
    int max;

    int count;

    std::vector<element> elements;
    std::mutex countMutex;
    std::atomic<bool> graphicClosed{false};

    int functionTotal;
    float functionAverage;

    // Functions
    void calculateAverage();
    void calculateExpectedCount();
    void calculateCurrentCount();
    void calculateCumulativeCount();
    void insertCurrentCount(bool graphic = true);
    void orderElements();

    // Validations
    bool inRange(int);
    static bool compareByCurrentCount(const element &a, const element &b);

public:
    // Constructor
    Generation(std::vector<int> elements, int min, int max,
               int (*function)(int),
               std::vector<int> (*cross)(std::vector<int>, int, int),
               std::vector<int> (*mutation)(std::vector<int>, int, int),
               int count);

    // Getters
    std::vector<element> getElements() const { return elements; }
    int getMin() const { return min; }
    int getMax() const { return max; }

    // Functions
    int (*function)(int);
    std::vector<int> (*cross)(std::vector<int>, int, int);
    std::vector<int> (*mutation)(std::vector<int>, int, int);

    // impresiones
    void printElements();
};

#endif // GENERATION_H
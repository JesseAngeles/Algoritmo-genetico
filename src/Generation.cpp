#include "Generation.h"

// Constructor
Generation::Generation(std::vector<int> initValues, int (*function)(int)) : function(function)
{
    for (int &value : initValues)
        if (inRange(value))
            this->values.push_back(value);

    this->size = this->values.size();
    this->currentCount = std::vector<int>(this->size);

    calculateAverage();
    calculateExpectedCount();

    this->randomizer = Randomizer(calculateComulativeCount());

    std::vector<std::thread> threads;
    for (int i = 0; i < COUNT; i++)
        threads.push_back(std::thread(&Generation::insertCurrentCount, this)); 

    for (auto &t : threads)
    {
        if (t.joinable())
            t.join();
    }

    print();
}

void Generation::calculateAverage()
{
    this->functionTotal = 0;
    for (const int value : this->values)
        this->functionTotal += this->function(value);

    this->functionAverage = this->functionTotal / static_cast<float>(this->size);
}

void Generation::calculateExpectedCount()
{
    float count = 0;
    for (int value : this->values)
    {
        int functionValue = this->function(value);
        float expected = functionValue / (this->functionAverage * this->size);
        this->expectedCount.push_back(expected);
        count += expected;
    }

    // Corrección para que la suma sea igual al numero de elementos
    this->expectedCount[0] += (1 - count);
}

std::vector<float> Generation::calculateComulativeCount()
{
    std::vector<float> cumulative;
    cumulative.push_back(this->expectedCount[0]);
    for (int i = 1; i < this->size; i++)
        cumulative.push_back(this->expectedCount[i] + cumulative[i - 1]);

    return cumulative;
}

void Generation::insertCurrentCount()
{
    int index = this->randomizer.random();        // Asegúrate de que random() esté bien definido
    std::lock_guard<std::mutex> lock(countMutex); // Bloqueo automático
    this->currentCount[index]++;    
}

// Validación
bool Generation::inRange(int value)
{
    if (MIN <= value && value <= MAX)
        return true;
    return false;
}

// Impresiones
void Generation::print()
{
    std::cout << "average:" << this->functionAverage << std::endl;
    for (int i = 0; i < this->size; i++)
    {
        std::cout << "f(" << values[i]
                  << ") = " << this->function(values[i])
                  << ", " << this->expectedCount[i]
                  << ", " << this->currentCount[i] << std::endl;
    }
}
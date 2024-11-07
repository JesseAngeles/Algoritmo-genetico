#include "Generation.h"

// Constructor
Generation::Generation(std::vector<int> initValues, int min, int max,
                       int (*function)(int),
                       std::vector<int> (*cross)(std::vector<int>),
                       std::vector<int> (*mutation)(std::vector<int>))
    : min(min), max(max), function(function), cross(cross), mutation(mutation)
{
    for (int &value : initValues)
        elements.push_back({value % (max + 1), 0, 0});

    this->size = this->elements.size();

    calculateAverage();
    calculateExpectedCount();
    calculateCumulativeCount();
    calculateCurrentCount();

    std::sort(elements.begin(), elements.end(), compareByCurrentCount);
}

void Generation::calculateAverage()
{
    functionTotal = 0;
    for (const element &element : elements)
        functionTotal += function(element.value);

    functionAverage = functionTotal / static_cast<float>(size);
}

void Generation::calculateExpectedCount()
{
    float count = 0;
    for (int i = 0; i < size; i++)
    {
        int functionValue = function(elements[i].value);
        float expected = functionValue / (functionAverage * size);
        elements[i].expectedCount = expected;
        count += expected;
    }

    // Corrección para que la suma sea igual al numero de elementos
    elements[0].expectedCount += (1 - count);
}

void Generation::calculateCumulativeCount()
{
    elements[0].cumulativeExpectedCount = elements[0].expectedCount;
    for (int i = 1; i < this->size; i++)
        elements[i].cumulativeExpectedCount = elements[i].expectedCount + elements[i - 1].cumulativeExpectedCount;
}

void Generation::calculateCurrentCount()
{
    std::thread graphicThread([this]()
                              { insertCurrentCount(true); });

    std::vector<std::thread> threads;
    int count = 0;

    while (count < TESTS)
    {
        threads.emplace_back([this]()
                             { insertCurrentCount(false); });
        count++;

        // Verificar la bandera para detener la creación de hilos
        if (graphicClosed)
            break;
    }

    if (graphicThread.joinable())
        graphicThread.join();

    for (std::thread &thread : threads)
        if (thread.joinable())
            thread.join();
}

void Generation::insertCurrentCount(bool graphic)
{
    int index = -1;

    if (graphic)
    {
        Grapher grapher;
        float random_num = random(1, 5);

        float count = 0;
        for (const auto &cls : elements)
        {
            grapher.drawDivisor(cls.cumulativeExpectedCount * 2 * M_PI, cls.cumulativeExpectedCount - count);
            count = cls.cumulativeExpectedCount;
        }

        index = grapher.draw(random_num);

        if (index == -1) // Si la ventana se cerró
        {
            graphicClosed = true;
            return;
        }
    }
    else
    {
        float random_num = random(0, 1);
        for (int i = 0; i < elements.size(); i++)
            if (random_num <= elements[i].cumulativeExpectedCount)
            {
                index = i;
                break;
            }
    }

    if (index >= 0)
    {
        std::lock_guard<std::mutex> lock(countMutex);
        elements[index].currentCount++;
    }
}

void Generation::orderElements()
{
    std::sort(elements.begin(), elements.end(), compareByCurrentCount);
}

bool compareByCurrentCount(const element &a, const element &b)
{
    return a.currentCount > b.currentCount; // Ordenar de mayor a menor
}
// Validación
bool Generation::inRange(int value)
{
    if (min <= value && value <= max)
        return true;
    return false;
}

bool Generation::compareByCurrentCount(const element &a, const element &b)
{
    return a.currentCount > b.currentCount; // Ordenar de mayor a menor
}
// Impresiones
void Generation::printElements()
{
    for (const element &element : elements)
    {
        std::cout << "f(" << element.value
                  << ") = " << this->function(element.value)
                  << ", " << element.expectedCount
                  << ", " << element.currentCount << std::endl;
    }
}
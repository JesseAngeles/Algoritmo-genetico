#include "Generation.h"

// Constructor
Generation::Generation(std::vector<int> initValues, int (*function)(int),
                       std::vector<int> (*cross)(std::vector<int>), std::vector<int> (*mutation)(std::vector<int>))
    : function(function), cross(cross), mutation(mutation)
{
    for (int &value : initValues)
        elements.push_back({value % (MAX + 1), 0, 0});

        // if (MIN <= value && value <= MAX)
        //     elements.push_back({value, 0, 0});

    this->size = this->elements.size();

    calculateAverage();
    calculateExpectedCount();
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

void Generation::calculateCurrentCount()
{
    this->randomizer = Randomizer(calculateComulativeCount());

    // Usa una lambda para invocar el método en un hilo
    std::thread graphicThread([this]()
                              { insertCurrentCount(true); });

    int count = 0;
    while (count < TESTS && graphicThread.joinable())
    {
        insertCurrentCount(false);
        count++;
    }

    graphicThread.join();
}

std::vector<float> Generation::calculateComulativeCount()
{
    std::vector<float> cumulative;
    cumulative.push_back(elements[0].expectedCount);
    for (int i = 1; i < this->size; i++)
        cumulative.push_back(elements[i].expectedCount + cumulative[i - 1]);

    return cumulative;
}

void Generation::insertCurrentCount(bool graphic)
{
    int index;
    if (graphic)
        index = this->randomizer.graphicRandom(); // Asegúrate de que random() esté bien definido
    else
        index = this->randomizer.random();

    std::lock_guard<std::mutex> lock(countMutex); // Bloqueo automático
    (elements[index].currentCount)++;
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
    if (MIN <= value && value <= MAX)
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
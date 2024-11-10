#include <vector>
#include <string>
#include <cmath>

#include "Randomizer.h"
#include "Binary.h"

void singlePointCrossover(std::pair<int, int> &father)
{
    // Randomizador
    Randomizer randomizer;

    // Codificar los números del padre a binario
    std::pair<std::vector<bool>, std::vector<bool>> binary = std::make_pair(
        DecimalToBinary(father.first), DecimalToBinary(father.second));

    // Selección de punto de cruce aleatorio
    int first_size = binary.first.size();
    int second_size = binary.second.size();

    int min_size = std::min(first_size, second_size);

    if (first_size == second_size)
        min_size--;

    int point = std::round(randomizer.generate(1, min_size));

    // Cruza en el punto seleccionado
    for (int i = 0; i < point; i++)
    {
        bool tmp = binary.first[i];
        binary.first[i] = binary.second[i];
        binary.second[i] = tmp;
    }

    // Decodificar de vuelta a decimal
    father.first = BinaryToDecimal(binary.first);
    father.second = BinaryToDecimal(binary.second);
}

void twoPointCrossover(std::pair<int, int> &father)
{
    // Randomizador
    Randomizer randomizer;

    // Codificar los números del padre a binario
    std::pair<std::vector<bool>, std::vector<bool>> binary = std::make_pair(
        DecimalToBinary(father.first), DecimalToBinary(father.second));

    // Seleccion de puntos
    int first_size = binary.first.size();
    int second_size = binary.second.size();

    int min_size = std::min(first_size, second_size) - 1;
    int first_point = std::round(randomizer.generate(0, min_size));
    int second_point = std::round(randomizer.generate(first_point, min_size));

    // Cruza
    for (int i = first_point; i <= second_point; i++)
    {
        bool tmp = binary.first[i];
        binary.first[i] = binary.second[i];
        binary.second[i] = tmp;
    }

    // Decodificar de vuelta a decimal
    father.first = BinaryToDecimal(binary.first);
    father.second = BinaryToDecimal(binary.second);
}

void uniformCrossover(std::pair<int, int> &father)
{
    // Randomizador
    Randomizer randomizer;
    
    // Codificar los números del padre a binario
    std::pair<std::vector<bool>, std::vector<bool>> binary = std::make_pair(
        DecimalToBinary(father.first), DecimalToBinary(father.second));

    // Cruza con mascara
    int min_size = std::min(binary.first.size(), binary.second.size());
    for (int i = 0; i < min_size; i++)
    {
        if (!std::round(randomizer.generate(0, 1)))
        {
            bool tmp = binary.first[i];
            binary.first[i] = binary.second[i];
            binary.second[i] = tmp;
        }
    }

    // Decodificar de vuelta a decimal
    father.first = BinaryToDecimal(binary.first);
    father.second = BinaryToDecimal(binary.second);
}

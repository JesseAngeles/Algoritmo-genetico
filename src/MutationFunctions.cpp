#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

#include <iostream>

#include "Randomizer.h"
#include "Binary.h"

void inversionMutation(int &organism)
{
    // Codificar el organismo
    std::vector<bool> binary = DecimalToBinary(organism);

    // Seleccion de puntos
    int first_point = std::round(random(0, binary.size() - 1));
    int second_point = std::round(random(first_point + 1, binary.size() - 1));

    // Inversion de cadena
    std::reverse(binary.begin() + first_point, binary.begin() + second_point + 1);

    // Decodificar de vuelta a decimal
    organism = BinaryToDecimal(binary);
}

void pointMutation(int &organism)
{
    // Codificar el organismo
    std::vector<bool> binary = DecimalToBinary(organism);

    // Inversion de punto
    int point = std::round(random(0, binary.size() - 1));
    binary[point] = !binary[point];

    // Decodificar de vuelta a decimal
    organism = BinaryToDecimal(binary);
}

void swapMutation(int &organism)
{
    // Codificar el organismo
    std::vector<bool> binary = DecimalToBinary(organism);

    // Inversion de punto
    int first_point = std::round(random(0, binary.size() - 1));
    int second_point;
    do
    {
        second_point = std::round(random(0, binary.size() - 1));
    } while (second_point == first_point);

    // Intercambio
    bool tmp = binary[first_point];
    binary[first_point] = binary[second_point];
    binary[second_point] = tmp;

    // Decodificar de vuelta a decimal
    organism = BinaryToDecimal(binary);
}

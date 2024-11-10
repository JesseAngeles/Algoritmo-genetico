#include "Binary.h"

std::vector<bool> DecimalToBinary(int num)
{
    std::vector<bool> str;
    if (num == 0) // Manejar el caso cuando num es 0
        str.push_back(0);

    while (num)
    {
        str.push_back(num & 1); // Añadir 1 o 0 dependiendo del bit menos significativo
        num >>= 1;
    }

    return str;
}

int BinaryToDecimal(const std::vector<bool> &binary)
{
    int decimal = 0;
    int power = 0;

    for (bool bit : binary)
    {
        if (bit) // Si el bit es 1, sumamos la potencia correspondiente de 2
            decimal += std::pow(2, power);
        power++; // Aumentar el exponente de 2
    }

    return decimal;
}

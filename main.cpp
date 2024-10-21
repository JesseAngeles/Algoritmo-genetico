#include <iostream>
#include <vector>
#include <set>
#include <bitset>

#include "Generation.h"

using namespace std;

struct functionEntry
{
    string name;
    int (*func)(int);
};

// Funciones principales
vector<int> getInitValues(int, char *[]);
functionEntry getInitFunction(int argc, char *argv[]);
vector<int> getValues(vector<element>);
vector<int> functionGenetic(vector<int>);

// Funciones de aplicacion
int functionSquare(int x) { return x * x; }
int functionCube(int x) { return x * x * x; }
int functionDoble(int x) { return 2 * x; }

// Funciones auxiliares
void print(vector<int>);

int main(int argc, char *argv[])
{
    set<vector<int>> historial;

    vector<int> initValues = getInitValues(argc, argv);
    functionEntry function = getInitFunction(argc, argv);

    // Generation generation(initValues, function.func);

    // vector<int> values = getValues(generation.getElements());

    // historial.insert(values);
    // vector<int> newValues = functionGenetic(values);

    // print(values);
    // print(newValues);

    do
    {
        print(initValues);
        Generation generation(initValues, function.func);
        vector<int> values = getValues(generation.getElements());

        if (historial.find(values) == historial.end())
            historial.insert(values);
        else // Ya se encontro esa generación anteriormente
            break;

        initValues = functionGenetic(values);
    } while (true);

    cout << "murio";

    return 0;
}

vector<int> getInitValues(int argc, char *argv[])
{
    vector<int> initValues;

    if (argc > 1)
    { // Los elementos iniciales se obtienen desde la ejecución
        for (int i = 1; i < argc - 1; i++)
        { // Excluir el último argumento (nombre de la función)
            string argument = argv[i];

            bool isNumber = true;
            for (char &c : argument)
                if (!isdigit(c))
                {
                    isNumber = false;
                    break;
                }

            if (isNumber)
                initValues.push_back(stoi(argument));
        }
    }
    else
    {
        cout << "faltan";
        exit(1);
    }

    return initValues;
}

functionEntry getInitFunction(int argc, char *argv[])
{
    vector<functionEntry> functions = {
        {"functionSquare", functionSquare},
        {"functionCube", functionCube},
        {"functionDoble", functionDoble}};

    if (argc > 1)
    {
        string name_function = argv[argc - 1];

        for (const functionEntry &function : functions)
            if (function.name == name_function)
                return function;
    }

    return functions[0];
}

vector<int> getValues(vector<element> elements)
{
    vector<int> values;
    for (element element : elements)
        values.push_back(element.value);

    return values;
}

vector<int> functionGenetic(vector<int> values)
{
    bitset<5> bestValue(values[0]);

    vector<int> newValues;

    for (int i = 1; i < values.size(); i++)
    {
        const int numBits = (2 * i) - 1;
        bitset<5> binary(values[i]);

        bitset<5> best = bestValue;

        // cout << "best: " << best << endl;
        // cout << "binary: " << binary << endl;

        // swap de valores binarios
        for (int j = 0; j < numBits; j++)
        {
            bool value = binary[j];
            binary[j] = best[j];
            best[j] = value;
        }

        // cout << "best modificado: " << best << endl;
        // cout << "binary modificado: " << binary << endl;

        newValues.push_back(int(best.to_ulong()));
        if (newValues.size() == values.size())
            break;

        newValues.push_back(int(binary.to_ulong()));
        if (newValues.size() == values.size())
            break;
    }

    return newValues;
}

void print(vector<int> values)
{
    cout << "Values: ";
    for (int i : values)
        cout << i << " ";
    cout << endl;
}
#include <iostream>
#include <vector>
#include <set>

#include "Generation.h"
#include "Randomizer.h"

#include "./src/Functions.cpp"
#include "./src/GeneticCrosses.cpp"
#include "./src/GeneticMutations.cpp"

#define DEFAULT_SIZE 4

using namespace std;

// Funciones principales

tuple<vector<int>, int, int, int, functionEntry, functionGenetic, functionGenetic> getParams(int, char *[]);

vector<int> getInitValues(int, char *[]);
tuple<functionEntry, functionGenetic, functionGenetic> getInitFunctions(int argc, char *argv[]);
vector<int> getValues(vector<element>);

// Funciones auxiliares
bool areEqual(vector<int>);
void print(vector<int>);

//! ./build/main.exe size min max is_rand function cross mutation
int main(int argc, char *argv[])
{
    // Read params
    tuple<vector<int>, int, int, int, functionEntry, functionGenetic, functionGenetic> data = getParams(argc, argv);
    vector<int> initValues = get<0>(data);
    int size = get<1>(data);
    int min = get<2>(data);
    int max = get<3>(data);
    functionEntry function = get<4>(data);
    functionGenetic cross = get<5>(data);
    functionGenetic mutation = get<6>(data);

    set<vector<int>> historial;
    int errorCount = 3;

    print(initValues);
    
    do
    {
        Generation generation(initValues, min, max, function.func, cross.func, mutation.func);
        vector<int> values = getValues(generation.getElements());

        if (historial.find(values) == historial.end())
        {
            historial.insert(values);
            initValues = generation.cross(values);
        }
        else if (areEqual(values)) // Son iguales todos
        {
            if (values[0] == max) // Son todos los mejores
                break;

            initValues = generation.mutation(values);
            cout << "Mutation: \n";
        }
        else // Ya se encontro esa generación anteriormente
        {
            errorCount--;
            cout << "Error count: " << errorCount << endl;
            initValues = generation.cross(values);
        }
        print(initValues);
    } while (errorCount);
    return 0;
}

tuple<vector<int>, int, int, int, functionEntry, functionGenetic, functionGenetic> getParams(int argc, char *argv[])
{
    vector<functionEntry> functions = {{"functionSquare", functionSquare}};
    vector<functionGenetic> crosses = {{"binarySwitch", geneticCrossBinarySwitch}};
    vector<functionGenetic> mutations = {{"randomSwitch", geneticMutationRandomSwitch}};

    vector<int> values;
    int size, min, max;
    functionEntry function;
    functionGenetic cross;
    functionGenetic mutation;

    try
    {
        size = stoi(argv[1]);
        min = stoi(argv[2]);
        max = stoi(argv[3]);
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: Argumentos iniciales deben ser números enteros válidos." << endl;
        exit(EXIT_FAILURE);
    }

    int index = 5;

    if (stoi(argv[4])) // random
    {
        for (int i = 0; i < size; i++)
            values.push_back(random(min, max));
    }
    else // Leer el tamaño de datos
    {
        index += size;

        for (int i = 5; i < index; i++)
        {
            string argument = argv[i];
            bool isNumber = true;
            for (char &c : argument)
                if (!isdigit(c))
                {
                    isNumber = false;
                    break;
                }

            if (isNumber)
                values.push_back(stoi(argument));
        }
    }

    for (const functionEntry &fun : functions)
        if (fun.name == argv[index++])
            function = fun;

    for (const functionGenetic &fun : crosses)
        if (fun.name == argv[index++])
            cross = fun;

    for (const functionGenetic &fun : mutations)
        if (fun.name == argv[index++])
            mutation = fun;

    return make_tuple(values, size, min, max, function, cross, mutation);
}

vector<int> getValues(vector<element> elements)
{
    vector<int> values;
    for (element element : elements)
        values.push_back(element.value);

    return values;
}

bool areEqual(vector<int> values)
{
    int initValue = values[0];
    for (int value : values)
        if (value != initValue)
            return false;

    return true;
}

void print(vector<int> values)
{
    cout << "Values: ";
    for (int i : values)
        cout << i << " ";
    cout << endl;
}
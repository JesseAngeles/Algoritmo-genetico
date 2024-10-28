#include <iostream>
#include <vector>
#include <set>

#include "Generation.h"

#include "./src/Functions.cpp"
#include "./src/GeneticCrosses.cpp"
#include "./src/GeneticMutations.cpp"

#define DEFAULT_SIZE 4

using namespace std;

// Funciones principales
vector<int> getInitValues(int, char *[]);
tuple<functionEntry, functionGenetic, functionGenetic> getInitFunctions(int argc, char *argv[]);
vector<int> getValues(vector<element>);

// Funciones auxiliares
bool areEqual(vector<int>);
void print(vector<int>);

int main(int argc, char *argv[])
{
    set<vector<int>> historial;

    vector<int> initValues = getInitValues(argc, argv);
    tuple<functionEntry, functionGenetic, functionGenetic> functions = getInitFunctions(argc, argv);
    functionEntry function = get<0>(functions);
    functionGenetic cross = get<1>(functions);
    functionGenetic mutation = get<2>(functions);

    int errorCount = 3;

    do
    {
        Generation generation(initValues, function.func, cross.func, mutation.func);
        vector<int> values = getValues(generation.getElements());

        if (historial.find(values) == historial.end())
        {
            historial.insert(values);
            initValues = generation.cross(values);
        }
        else if (areEqual(values)) // Son iguales todos
        {
            if (values[0] == MAX) // Son todos los mejores
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

vector<int> getInitValues(int argc, char *argv[])
{
    vector<int> initValues;

    if (argc > 1)
    { // Los elementos iniciales se obtienen desde la ejecución
        for (int i = 1; i < argc; i++)
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
        initValues = {13, 24, 8, 19};
    }

    return initValues;
}

tuple<functionEntry, functionGenetic, functionGenetic> getInitFunctions(int argc, char *argv[])
{

    vector<functionEntry> functions = {{"functionSquare", functionSquare}};

    vector<functionGenetic> crosses = {{"binarySwitch", geneticCrossBinarySwitch}};

    vector<functionGenetic> mutations = {{"randomSwitch", geneticMutationRandomSwitch}};

    functionEntry entry_function = functions[0];
    functionGenetic cross = crosses[0];
    functionGenetic mutation = mutations[0];

    if (argc > 1)
    {
        vector<string> param_functions;
        for (int i = 1; i < argc; i++)
        {
            string argument = argv[i];

            bool isNumber = true;
            for (char &c : argument)
                if (!isdigit(c))
                {
                    isNumber = false;
                    break;
                }

            if (!isNumber)
                param_functions.push_back(string(argument));
        }

        if (param_functions.size() >= 1) // Busca la función correspondiente en `functions`
        {
            for (const functionEntry &fun : functions)
                if (fun.name == param_functions[0])
                    entry_function = fun;

            if (param_functions.size() >= 2) // Busca la función correspondiente en `crosses`
            {
                for (const functionGenetic &fun : crosses)
                    if (fun.name == param_functions[1])
                        cross = fun;

                if (param_functions.size() >= 3) // Busca la función correspondiente en `mutations`
                    for (const functionGenetic &fun : mutations)
                        if (fun.name == param_functions[2])
                            mutation = fun;
            }
        }
    }

    return make_tuple(entry_function, cross, mutation);
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
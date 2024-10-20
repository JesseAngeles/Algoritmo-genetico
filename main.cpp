#include <iostream>
#include <vector>

#include "Generation.h"

using namespace std;

// Funciones principales
vector<int> getInitValues(int, char *[]);

// Funciones de aplicacion
struct functionEntry
{
    string name;
    int (*func)(int);
};

functionEntry getInitFunction(int argc, char *argv[]);
int functionSquare(int x) { return x * x; }
int functionCube(int x) { return x * x * x; }
int functionDoble(int x) { return 2 * x; }

int main(int argc, char *argv[])
{
    vector<int> initValues = getInitValues(argc, argv);
    functionEntry function = getInitFunction(argc, argv);
    Generation generation(initValues, function.func);

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
clear

g++ -c -I./include src/middleware/Binary.cpp    -o build/Binary.o
g++ -c -I./include src/Grapher.cpp    -o build/Grapher.o 
g++ -c -I./include src/Randomizer.cpp -o build/Randomizer.o
g++ -c -I./include src/Generation.cpp -o build/Generation.o
g++ -c -I./include main.cpp           -o build/main.o

g++ build/Binary.o build/Grapher.o build/Randomizer.o build/Generation.o build/main.o -o build/main.exe -Iinclude -lsfml-graphics -lsfml-window -lsfml-system
./build/main.exe

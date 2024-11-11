#ifndef GRAPHER_H
#define GRAPHER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace sf;

class Grapher
{
private:
    // Atributes
    int width;
    int height;

    int x_center;
    int y_center;

    std::string name;
    Color background;

    // Texto
    Font font;
    std::vector<Text> texts;

    // Lineas
    std::vector<VertexArray> axes;
    std::vector<VertexArray> lines;

    // Circulos
    std::vector<CircleShape> circles;

    // Rectangulos
    std::vector<RectangleShape> rectangles;

public:
    Grapher(int = 250, int = 250, std::string content = "Roulette", Color background = {255, 255, 255});

    void drawText(std::string content, int fontSize, float x, float y, Color color);
    void drawRectangle(float width, float height, float x, float y, Color color);
    void drawDivisor(float angle, float value);
    void drawCircle(float x, float y, float radius, Color color);
    void moveLines(float angle);
    int draw(float factor);
    int getAngle();

    // Getters
    RenderWindow window;
};

#endif // GRAPHER_H
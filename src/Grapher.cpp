#include "Grapher.h"

Grapher::Grapher(int width, int height, std::string name, Color background)
    : width(width), height(height), name(name), window(VideoMode(width, height), name), background(background)
{
    if (!this->font.loadFromFile("resources/Roboto-Medium.ttf"))
        exit(1);

    x_center = width / 2;
    y_center = height / 2;

    drawCircle(x_center, y_center, 100, {250, 0, 0}, false);
}

// Dibujar texto
void Grapher::drawText(std::string content, int fontSize, float x, float y, Color color, bool isScaled)
{
    Text text;
    text.setFont(this->font);
    text.setString(content);
    text.setCharacterSize(fontSize);
    text.setFillColor(color);
    text.setPosition(x, y);

    this->texts.push_back(text);
}

void Grapher::drawDivisor(float angle)
{
    float x = cos(angle);
    float y = sin(angle);

    VertexArray line(Lines, 2);

    x = (x * 100) + x_center;
    y = y_center - (y * 100);

    line[0].position = Vector2f(width / 2, height / 2);
    line[1].position = Vector2f(x, y);

    line[0].color = line[1].color = {0, 0, 0};

    this->lines.push_back(line);
}

void ::Grapher::drawCircle(float x, float y, float radius, Color color, bool isScaled)
{
    CircleShape circle(radius);
    circle.setPosition(x - radius, y - radius);
    circle.setFillColor(color);

    this->circles.push_back(circle);
}

int Grapher::draw(float factor)
{

    float speed = factor * 500;
    float seconds = 0.05f; // Tiempo inicial para el primer mensaje
    float time = 5.0f;     // Tiempo límite para cerrar la ventana

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.getElapsedTime();
        float deltaTime = elapsed.asSeconds();

        moveLines(speed);

        // Condición para imprimir mensaje periódicamente
        if (deltaTime > seconds && speed > 0)
        {
            speed -= factor * 5;
            // Reiniciar el reloj para la siguiente iteración
            clock.restart();
        }

        // Cerrar la ventana si han pasado más de `time` segundos
        if (deltaTime > 3.0f)
        {
            window.close();
        }

        window.clear(background);

        // Dibujar elementos estaticos
        if (!texts.empty())
            for (const Text &text : texts)
                window.draw(text);

        if (!circles.empty())
            for (const CircleShape &circle : circles)
                window.draw(circle);

        if (!lines.empty())
            for (const VertexArray &line : lines)
                window.draw(line);

        window.display();
    }

    return getAngle();
}

void Grapher::moveLines(float speed)
{
    for (int i = 0; i < lines.size(); i++)
    {
        // Calculamos el ángulo actual de la línea y lo convertimos a grados
        float dx = lines[i][1].position.x - x_center;
        float dy = y_center - lines[i][1].position.y; // Invertimos para que Y crezca hacia arriba

        float angle = atan2(dy, dx) * (180 / M_PI); // Convertimos el ángulo a grados

        // Aseguramos que el ángulo esté entre 0 y 360 grados
        if (angle < 0)
            angle += 360;

        // Ajustamos el ángulo sumando velocidad
        angle += speed * 0.0001;

        // Normalizamos el ángulo para que esté dentro del rango [0, 360)
        angle = fmod(angle, 360.0f);

        // Calculamos las nuevas posiciones en X e Y en radianes
        float radAngle = angle * (M_PI / 180); // Convertimos a radianes

        float x = cos(radAngle); // Calculamos el coseno en radianes
        float y = sin(radAngle); // Calculamos el seno en radianes

        // Reescalamos y ajustamos las posiciones de acuerdo al centro
        x = (x * 100) + x_center; // Posición X
        y = y_center - (y * 100); // Posición Y

        // Asignamos las nuevas posiciones a la línea
        lines[i][1].position.x = x;
        lines[i][1].position.y = y;

        // break;  // Solo mover una línea
    }
}

int Grapher::getAngle()
{
    int closestIndex = -1; // Almacena el índice de la línea más cercana a 0°
    float closestAngle = 360.0f; // El ángulo más cercano a 0° que hemos encontrado

    for (int i = 0; i < lines.size(); i++)
    {
        // Calculamos las diferencias en X e Y
        float dx = lines[i][1].position.x - x_center;
        float dy = y_center - lines[i][1].position.y; // Invertimos Y para que crezca hacia arriba

        // Calculamos el ángulo en grados
        float angle = atan2(dy, dx) * (180 / M_PI); 

        // Ajustamos el ángulo para que esté en el rango [0, 360)
        if (angle < 0)
            angle += 360;

        std::cout << "Angle for line " << i << ": " << angle << std::endl;

        // Comprobamos si este ángulo es el más cercano a 0°
        if (abs(angle) < closestAngle)
        {
            closestAngle = abs(angle); // Guardamos el ángulo más cercano
            closestIndex = i;          // Guardamos el índice de la línea más cercana
        }
    }

    // Imprimimos el resultado
    std::cout << "Line closest to 0° has index: " << closestIndex << " with angle: " << closestAngle << std::endl;

    return closestIndex;
}
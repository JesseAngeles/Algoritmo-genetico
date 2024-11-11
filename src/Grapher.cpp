#include "Grapher.h"

Grapher::Grapher(int width, int height, std::string name, Color background)
    : width(width), height(height), name(name),
      window(VideoMode(width, height), name, Style::Close), 
      background(background)
{
    if (!this->font.loadFromFile("resources/Roboto-Medium.ttf"))
        exit(1);

    x_center = width / 2;
    y_center = height / 2;

    drawCircle(x_center, y_center, 100, {37, 206, 209});
    drawRectangle(50, 5, x_center + 95, y_center, {4, 67, 137});
}

// Dibujar texto
void Grapher::drawText(std::string content, int fontSize, float x, float y, Color color)
{
    Text text;
    text.setFont(this->font);
    text.setString(content);
    text.setCharacterSize(fontSize);
    text.setFillColor(color);
    text.setPosition(x, y);

    this->texts.push_back(text);
}

void Grapher::drawRectangle(float width, float height, float x, float y, Color color)
{
    RectangleShape rectangle(Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setOutlineThickness(0);
    rectangle.setFillColor(color);

    this->rectangles.push_back(rectangle);
}

void Grapher::drawDivisor(float angle, float value)
{
    float x = cos(angle);
    float y = sin(angle);

    float label_x = cos(angle - 0.2);
    float label_y = sin(angle - 0.2);

    drawText(std::to_string(value), 12, (label_x * 75) + x_center, y_center - (label_y * 75), {0, 0, 0});

    VertexArray line(Lines, 2);

    x = (x * 100) + x_center;
    y = y_center - (y * 100);

    line[0].position = Vector2f(width / 2, height / 2);
    line[1].position = Vector2f(x, y);

    line[0].color = line[1].color = {0, 0, 0};

    this->lines.push_back(line);
}

void ::Grapher::drawCircle(float x, float y, float radius, Color color)
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

    Clock clock;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                return -1;
            }
        }

        Time elapsed = clock.getElapsedTime();
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
            window.close();

        window.clear(background);

        // Dibujar elementos estaticos
        if (!circles.empty())
            for (const CircleShape &circle : circles)
                window.draw(circle);

        if (!lines.empty())
            for (const VertexArray &line : lines)
                window.draw(line);

        if (!rectangles.empty())
            for (const RectangleShape &rectangle : rectangles)
                window.draw(rectangle);

        if (!texts.empty())
            for (const Text &text : texts)
                window.draw(text);

        window.display();
    }

    return getAngle();
}

void Grapher::moveLines(float speed)
{
    if (speed <= 0)
        return;

    for (int i = 0; i < lines.size(); i++)
    {
        // Calculamos el ángulo actual de la línea y lo convertimos a grados
        float dx = lines[i][1].position.x - x_center;
        float dy = y_center - lines[i][1].position.y;

        float label_dx = texts[i].getPosition().x - x_center;
        float label_dy = y_center - texts[i].getPosition().y;

        // Convertimos el ángulo a grados
        float angle = atan2(dy, dx) * (180 / M_PI);
        float label_angle = atan2(label_dy, label_dx) * (180 / M_PI);

        // Aseguramos que el ángulo esté entre 0 y 360 grados
        if (angle < 0)
            angle += 360;
        if (label_angle < 0)
            label_angle += 360;

        // Ajustamos el ángulo sumando velocidad
        angle += speed * 0.0001;
        label_angle += speed * 0.0001;

        // Normalizamos el ángulo para que esté dentro del rango [0, 360)
        angle = fmod(angle, 360.0f);
        label_angle = fmod(label_angle, 360.0f);

        // Calculamos las nuevas posiciones en X e Y en radianes
        float radAngle = angle * (M_PI / 180);
        float label_radAngle = label_angle * (M_PI / 180);

        float x = cos(radAngle);
        float y = sin(radAngle);

        float label_x = cos(label_radAngle);
        float label_y = sin(label_radAngle);

        // Reescalamos y ajustamos las posiciones de acuerdo al centro
        x = (x * 100) + x_center; // Posición X
        y = y_center - (y * 100); // Posición Y

        label_x = (label_x * 75) + x_center;
        label_y = y_center - (label_y * 75);

        // Asignamos las nuevas posiciones a la línea
        lines[i][1].position.x = x;
        lines[i][1].position.y = y;

        texts[i].setPosition(label_x, label_y);
    }
}

int Grapher::getAngle()
{
    int closestIndex = -1;       // Almacena el índice de la línea más cercana a 0°
    float closestAngle = 180.0f; // El ángulo más cercano a 0° que hemos encontrado

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

        // Comprobamos si este ángulo es el más cercano a 0°
        if (abs(angle) < closestAngle)
        {
            closestAngle = abs(angle); // Guardamos el ángulo más cercano
            closestIndex = i;          // Guardamos el índice de la línea más cercana
        }
    }

    return closestIndex;
}
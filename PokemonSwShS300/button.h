#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace sf;
class Button {
private:
    double x;
    double y;
    double width;
    double height;
    std::string text;
    sf::Color color;
public:
    Button() : x(0), y(0), width(0), height(0), text(""), color(sf::Color::Red) {};
    Button(double x, double y, double width, double height, std::string text)
        : x(x), y(y), width(width), height(height), text(text), color(sf::Color::Red) {};
    Button(const Button& other) : x(other.x), y(other.y), width(other.width), height(other.height), text(other.text), color(other.color) {};
    ~Button() {};

    void setColor(double first, double second, double third) {
        color = sf::Color(first, second, third);
    }

    void setColor(vector<int> &colors) {
        color = sf::Color(colors[0], colors[1], colors[2]);
    }
    void setPosition(double x_1, double y_1) {
        x = x_1;
        y = y_1;
    }
    void setSize(double w, double h) {
        width = w;
        height = h;
    }

    void setText(const std::string text_1) {
        text = text_1;
    }

    void drawButton(RenderWindow& window) {
        RectangleShape button(Vector2f(width, height));
        button.setPosition(x, y);
        button.setFillColor(color);
        button.setOutlineColor(Color::Black);
        button.setOutlineThickness(5);
        window.draw(button);

        Font font;
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");

        Text buttonText;
        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setPosition(x + width / 2 - buttonText.getLocalBounds().width / 2, y + height / 2 - 10);
        window.draw(buttonText);
    }

    bool isButtonHovered(sf::Vector2f mousePos) {
        return mousePos.x >= this->x && mousePos.x <= this->x + this->width &&
            mousePos.y >= this->y && mousePos.y <= this->y + this->height;
    }

};
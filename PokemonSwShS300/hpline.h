#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace sf;
class HPLine {
private:
    double x;
    double y;
    double width;
    double height;
    double begHealthDoub;
    std::string text;
    sf::Color color;
public:
    HPLine() : x(0), y(0), width(0), height(0), text(""), color(sf::Color::Red), begHealthDoub(300) {};
    HPLine(double x, double y, double width, double height, std::string text, double begHealthDoub)
        : x(x), y(y), width(width), height(height), text(text), color(sf::Color::Red), begHealthDoub(begHealthDoub) {};
    HPLine(const HPLine& other) : x(other.x), y(other.y), width(other.width), height(other.height), text(other.text), color(other.color), begHealthDoub(other.begHealthDoub){};
    ~HPLine() {};

    void setColor(double first, double second, double third) {
        color = sf::Color(first, second, third);
    }

    void setColor(vector<int>& colors) {
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
        RectangleShape redRect(Vector2f(width, height));
        redRect.setPosition(x, y);
        redRect.setFillColor(Color(204, 0, 0));
        redRect.setOutlineColor(Color::Black);
        redRect.setOutlineThickness(5);
        window.draw(redRect);
    
        double newWidth;
        if (stod(text) >= 0.0) {
            newWidth = width * stod(text) / begHealthDoub;
        }
        else {
            newWidth = 1.0;
        }
        RectangleShape greenRect(Vector2f(newWidth, height));
        greenRect.setPosition(x, y);
        greenRect.setFillColor(Color(0, 153, 0));
        greenRect.setOutlineColor(Color::Black);
        greenRect.setOutlineThickness(5);
        window.draw(greenRect);

        Font font;
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");


        double num = begHealthDoub;
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << num;
        std::string str = stream.str();

        Text buttonText;
        buttonText.setFont(font);
        buttonText.setString(text + '/' + str);
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
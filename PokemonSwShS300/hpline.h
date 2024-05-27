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
    pair<int, int> types;
    string namePok;
public:
    HPLine() : x(0), y(0), width(0), height(0), text(""), color(sf::Color::Red), begHealthDoub(300), types({ 0, 0 }), namePok("Eternatus") {};
    HPLine(double x, double y, double width, double height, std::string text, double begHealthDoub, pair<int, int> types, string namePok)
        : x(x), y(y), width(width), height(height), text(text), color(sf::Color::Red), begHealthDoub(begHealthDoub), types(types), namePok(namePok) {};
    HPLine(const HPLine& other) : x(other.x), y(other.y), width(other.width), height(other.height), 
        text(other.text), color(other.color), begHealthDoub(other.begHealthDoub), types(other.types), namePok(other.namePok){};
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

    void drawHPLine(sf::RenderWindow& window) 
    {
        sf::RectangleShape redRect(sf::Vector2f(width, height));
        redRect.setPosition(x, y);
        redRect.setFillColor(sf::Color(204, 0, 0));
        redRect.setOutlineColor(sf::Color::Black);
        redRect.setOutlineThickness(5);
        window.draw(redRect);

        double newWidth;
        if (stod(text) >= 0.0) {
            newWidth = width * stod(text) / begHealthDoub;
        }
        else {
            newWidth = 1.0;
        }
        sf::RectangleShape greenRect(sf::Vector2f(newWidth, height));
        greenRect.setPosition(x, y);
        greenRect.setFillColor(sf::Color(0, 153, 0));
        greenRect.setOutlineColor(sf::Color::Black);
        greenRect.setOutlineThickness(5);
        window.draw(greenRect);

        sf::Font font;
        font.loadFromFile("C:/Windows/Fonts/comic.ttf");

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

        // Отображение имени покемона
        sf::Text nameText;
        nameText.setFont(font);
        nameText.setString(namePok);
        nameText.setCharacterSize(40);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(x + 140, y - 65);
        window.draw(nameText);

        Texture texture1, texture2;

        string first = "img/type/" + to_string(types.first) + ".png";
        string second= "img/type/" + to_string(types.second) + ".png";

        if (!texture1.loadFromFile(first)) 
        { 
            return; 
        }
        if (!texture2.loadFromFile(second))
        {
            return;
        }
        Sprite sprite1(texture1), sprite2(texture2);

        sprite1.setTexture(texture1);
        sprite2.setTexture(texture2);

        sprite1.setScale(0.5, 0.5); // Уменьшаем масштаб текстур, чтобы они поместились в квадраты
        sprite1.setPosition(x - 3, y - 75);
        window.draw(sprite1);

        sprite2.setScale(0.5, 0.5);
        sprite2.setPosition(x + 60, y - 75);
        window.draw(sprite2);
    }

    bool isButtonHovered(sf::Vector2f mousePos) {
        return mousePos.x >= this->x && mousePos.x <= this->x + this->width &&
            mousePos.y >= this->y && mousePos.y <= this->y + this->height;
    }

};
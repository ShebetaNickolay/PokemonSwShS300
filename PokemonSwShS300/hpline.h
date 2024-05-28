#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace sf;

class HPLine {
private:
    double x;               // Abscissa 
    double y;               // Ordinate
    double width;           // Line width
    double height;          // Line height
    double begHealthDoub;   // The initial health of the PokeMon
    string text;            // The curr health
    Color color;            // Color
    pair<int, int> types;   // Types of PokeMon
    string namePok;         // Name of PokeMon
public:
    HPLine() : x(0), y(0), width(0), height(0), text(""), color(Color::Red), begHealthDoub(300), types({ 0, 0 }), namePok("Eternatus") {};
    
    HPLine(double x, double y, double width, double height, string text, double begHealthDoub, pair<int, int> types, string namePok)
        : x(x), y(y), width(width), height(height), text(text), color(Color::Red), begHealthDoub(begHealthDoub), types(types), namePok(namePok) {};
    
    HPLine(const HPLine& other) : x(other.x), y(other.y), width(other.width), height(other.height), 
        text(other.text), color(other.color), begHealthDoub(other.begHealthDoub), types(other.types), namePok(other.namePok){};
    ~HPLine() {};

    // Setting the color through 3 parameters
    void setColor(double first, double second, double third) {
        color = Color(first, second, third);
    }

    // Setting the color through 1 vector
    void setColor(vector<int>& colors) {
        color = Color(colors[0], colors[1], colors[2]);
    }

    // Setting positions on the field
    void setPosition(double x_1, double y_1) {
        x = x_1;
        y = y_1;
    }

    // Setting the band sizes
    void setSize(double w, double h) {
        width = w;
        height = h;
    }

    // Installing the current HP
    void setText(const std::string text_1) {
        text = text_1;
    }

    // Drawing a health bar with setting the name and types
    void drawHPLine(RenderWindow& window) 
    {
        // The red rectangle
        RectangleShape redRect(Vector2f(width, height));
        redRect.setPosition(x, y);
        redRect.setFillColor(Color(204, 0, 0));
        redRect.setOutlineColor(Color::Black);
        redRect.setOutlineThickness(5);
        window.draw(redRect);

        // The green rectangle
        double newWidth = (stod(text) >= 0.0) ? width * stod(text) / begHealthDoub : 1.0;

        RectangleShape greenRect(Vector2f(newWidth, height));
        greenRect.setPosition(x, y);
        greenRect.setFillColor(Color(0, 153, 0));
        greenRect.setOutlineColor(Color::Black);
        greenRect.setOutlineThickness(5);
        window.draw(greenRect);

        Font font;
        font.loadFromFile("C:/Windows/Fonts/comic.ttf");

        // Current health / Initial
        double num = begHealthDoub;
        stringstream stream;
        stream << fixed << setprecision(2) << num;
        string str = stream.str();

        Text buttonText;
        buttonText.setFont(font);
        buttonText.setString(text + '/' + str);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(Color::Black);
        buttonText.setPosition(x + width / 2 - buttonText.getLocalBounds().width / 2, y + height / 2 - 10);
        window.draw(buttonText);

        // Displaying the Pokemon name
        Text nameText;
        nameText.setFont(font);
        nameText.setString(namePok);
        nameText.setCharacterSize(40);
        nameText.setFillColor(Color::White);
        nameText.setPosition(x + 140, y - 65);
        window.draw(nameText);

        Texture texture1, texture2;

        string first = "img/type/" + to_string(types.first) + ".png";
        string second= "img/type/" + to_string(types.second) + ".png";

        if (!texture1.loadFromFile(first)) { return; }
        if (!texture2.loadFromFile(second)){ return; }

        Sprite sprite1(texture1), sprite2(texture2);

        sprite1.setTexture(texture1);
        sprite2.setTexture(texture2);

        sprite1.setScale(0.5, 0.5);
        sprite1.setPosition(x - 3, y - 75);
        window.draw(sprite1);

        sprite2.setScale(0.5, 0.5);
        sprite2.setPosition(x + 60, y - 75);
        window.draw(sprite2);
    }

};
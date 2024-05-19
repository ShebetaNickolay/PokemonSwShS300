#include <SFML/Graphics.hpp>
#include "field.h" 

using namespace sf;

int main() {
    cout << 1;
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Pokemon. Galar forest battle.");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        drawField(window);
        window.display();
    }

   
    return 0;
}
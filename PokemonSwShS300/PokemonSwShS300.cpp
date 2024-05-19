#include <SFML/Graphics.hpp>
#include "field.h" 

using namespace sf;

void info(PokeMon your) {
    cout << "Имя ПокеМона: " << your.getName() << '\n';
    cout << "Типы ПокеМона: " << your.getTypes().first << ' ' << your.getTypes().second << '\n';
    cout << "Принадлежность: " << your.getOwner() << '\n';
    vector<PCommand> list = your.getMoves();
    for (int i = 0; i < list.size(); i++) {
        cout << list[i].getName() << '\n';
    }
}

pair<PokeMon, PokeMon> create() {
    vector<PCommand> yourList, enemyList;

    yourList.push_back(PCommand(50, 0, 0, 1, "Arm Thrust"));
    yourList.push_back(PCommand(25, 0, 0, 2, "Body Press"));
    yourList.push_back(PCommand(150, 0, 0, 3, "Close Combatt"));
    yourList.push_back(PCommand(0, 100, 0, 4, "Arm Thrust"));

    enemyList.push_back(PCommand(75, 0, 1, 1, "Aqua Jet"));
    enemyList.push_back(PCommand(25, 25, 1, 2, "G-Max Cannonade"));
    enemyList.push_back(PCommand(100, 0, 1, 3, "G-Max Foam Burst"));
    enemyList.push_back(PCommand(0, 150, 1, 4, "Razor Shell"));

    PokeMon your = PokeMon(300, 10, 20, yourList, 0, 1, 2, "Snom");
    PokeMon enemy = PokeMon(250, 10, 20, enemyList, 1, 3, 4, "Sobble");

    // info(your);


    return make_pair(your, enemy);
}

int main() {
    pair<PokeMon, PokeMon> tmp = create();
    RenderWindow window(VideoMode(1600, 1000), "Pokemon. Galar forest battle.");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        drawField(window, tmp);
        window.display();
    }


    return 0;
}
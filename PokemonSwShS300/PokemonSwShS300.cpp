#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "pokemon.h"
#include "command.h"
#include "field.h" 

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace sf;
using namespace std;

vector<vector<double>> create_type_matrix() {
    ifstream file("txtFile/type_matrix.txt");
    vector<vector<double>> result(18, vector<double>(18, 0));

    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 18; j++) {
            file >> result[i][j];
        }
    }
    file.close();
    return result;
}

vector<PCommand> create_list_of_commands() {
    ifstream file("txtFile/your_command_list.txt");
    vector<PCommand> result;

    double damage, healing;
    bool owner, status;
    int type;
    string name;


    if (file.is_open()) {
        while (file >> damage >> healing >> owner >> type >> name >> status) {
            result.push_back(PCommand(damage, healing, owner, type, name, status));
        }
    }
    file.close();
    return result;
}


vector<PokeMon> create_list_of_pokemon(vector<PCommand>& listOfCommands, bool flag) {
    string nameF = "";
    if (flag) {
        nameF = "txtFile/enemy_pokemon_list.txt";
    }
    else {
        nameF = "txtFile/your_pokemon_list.txt";
    }
    ifstream file(nameF);
    vector<PokeMon> result;
    double health, attack, defense;
    int type1, type2;
    string name;
    int cFrame, widthPic, heightPic;

    int n = listOfCommands.size();

    if (file.is_open()) {
        while (file >> health >> attack >> defense >> type1 >> type2 >> name >> cFrame >> widthPic >> heightPic) {
            vector<PCommand> comm;
            comm.push_back(listOfCommands[rand() % n]);
            comm.push_back(listOfCommands[rand() % n]);
            comm.push_back(listOfCommands[rand() % n]);
            comm.push_back(listOfCommands[rand() % n]);
            for (int i = 0; i < 4; i++) {
                comm[i].owner = flag;
            }
            result.push_back(PokeMon(health, attack, defense, comm, type1, type2, name, cFrame, widthPic, heightPic));
        }
    }
    file.close();
    return result;
}


pair<vector<PokeMon>, vector<PokeMon>> create_list(vector<PokeMon>& list_of_your_pok, vector<PokeMon>& list_of_enemy_pok) {
    int n = list_of_your_pok.size();
    int m = list_of_enemy_pok.size();
    vector<PokeMon> first = { list_of_your_pok[rand() % n],
                             list_of_your_pok[rand() % n],
                             list_of_your_pok[rand() % n],
                              list_of_your_pok[rand() % n],
                            list_of_your_pok[rand() % n],
                              list_of_your_pok[rand() % n] };

    for (int i = 0; i < first.size(); i++) {
        first[i].owner = 0;
    }
    vector<PokeMon> second = { list_of_enemy_pok[rand() % m],
                              list_of_enemy_pok[rand() % m],
                              list_of_enemy_pok[rand() % m],
                              list_of_enemy_pok[rand() % m],
                            list_of_enemy_pok[rand() % m],
                              list_of_enemy_pok[rand() % m] };
    for (int i = 0; i < second.size(); i++) {
        second[i].owner = 1;
    }
    return make_pair(first, second);
}

int main() 
{
    srand(time(NULL));

    vector<vector<double>> typeMatrix = create_type_matrix();
    vector<PCommand> commandList = create_list_of_commands();
    vector<PokeMon> pokemonListE = create_list_of_pokemon(commandList, 1);
    vector<PokeMon> pokemonListY = create_list_of_pokemon(commandList, 0);
    pair<vector<PokeMon>, vector<PokeMon>> list_of_op = create_list(pokemonListY, pokemonListE);

    pair<PCommand, int> weatherCommand = { commandList[0], -1 };

    int ind1 = 0, ind2 = 0;
    pair<PokeMon, PokeMon> tmp = { list_of_op.first[ind1], list_of_op.second[ind2] };

    RenderWindow window(VideoMode(1600, 1000), "Pokemon. Galar forest battle.");

    Music music;
    if (!music.openFromFile("music/battle1.mp3"))
    {
        return -1;
   }

   music.play();

    string situation = "The fight has begun. ";
    situation += tmp.first.getName();
    situation += " VS ";
    situation += tmp.second.getName();

    sf::Clock animationClock;
    int currentFrame = 0;

    while (window.isOpen())
    {
        window.clear();
        Texture texture;
        if (!texture.loadFromFile("img/battle_phon/forest2.png")) { return 0; }
        Sprite sprite(texture);

        sprite.setTexture(texture);
        sprite.setScale((float)window.getSize().x / sprite.getLocalBounds().width,
            (float)window.getSize().y / sprite.getLocalBounds().height);

        sprite.setPosition(0, 0);
        window.draw(sprite);

        sf::Texture animationTexture;
        if (!animationTexture.loadFromFile(tmp.second.getPath())) {
            // Ошибка при загрузке текстуры
            return 0;
        }

        int frameCount = tmp.second.getcFrame();
        int frameWidth = tmp.second.getWidth() / frameCount; // Ширина кадра
        int frameHeight = tmp.second.getHeight(); // Высота кадра

        sf::Sprite animationSprite(animationTexture);
        animationSprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
        animationSprite.setScale(3.5f, 3.5f);

        float enemyPositionX = 1060; // Правый край окна минус ширина текстуры
        float enemyPositionY = 175; // Позиция по Y (может быть изменена по необходимости)

        animationSprite.setPosition(enemyPositionX, enemyPositionY);

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (animationClock.getElapsedTime().asSeconds() >= 0.005f) {
            currentFrame = (currentFrame + 1) % frameCount;
            animationSprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
        }

        window.draw(animationSprite);

        drawField(window, tmp, situation, typeMatrix, weatherCommand);
        window.display();

        if (tmp.first.getHealth() <= 0.0) {
            if (ind1 + 1 < list_of_op.first.size()) {
                ind1++;
                tmp.first = list_of_op.first[ind1];
            }
            else {
                situation = "Congratulations, you've lost!";
            }
        }

        if (tmp.second.getHealth() <= 0.0) {
            if (ind2 + 1 < list_of_op.second.size()) {
                ind2++;
                tmp.second = list_of_op.second[ind2];
            }
            else {
                situation = "You have won! Bake a punching bag!";

            }
        }
    }



    return 0;
}
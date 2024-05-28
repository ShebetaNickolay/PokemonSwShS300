#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "pokemon.h"
#include "command.h"
#include "field.h" 
#include "inst.h"

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace sf;
using namespace std;

const float enemyPositionX = 1200;  // The position of the enemy PokeMon
const float enemyPositionY = 325;

const float yourPositionX = 200;  // The position of the your PokeMon
const float yourPositionY = 700;

int main() 
{
    srand(time(NULL));
    // Creating lists for further play.
    vector<vector<double>> typeMatrix = create_type_matrix();                   // The matrix of types needed to increase/decrease/reset damage
    vector<PCommand> commandList = create_list_of_commands();                   // List of techniques used by PokeMon
    vector<PokeMon> pokemonListE = create_list_of_pokemon(commandList, 1);      // The list of Pokemon available to the opponent
    vector<PokeMon> pokemonListY = create_list_of_pokemon(commandList, 0);      // The list of PokeMon available to you
    pair<vector<PokeMon>, vector<PokeMon>> list_of_op = create_list(pokemonListY, pokemonListE);  // first - You, secoond - Enemy

    // A technique that treats the Pokemon that used it
    // And beating the enemy and beating the enemy for several moves
    pair<PCommand, int> weatherCommand = { commandList[0], -1 };              

    int indexYou = 0, indEnemy = 0; // The current duel between yours and the enemy monster
    pair<PokeMon, PokeMon> currDuel = { list_of_op.first[indexYou], list_of_op.second[indEnemy] };

    RenderWindow window(VideoMode(1600, 1000), "Pokemon. Galar forest battle.");

    Music music;   // Music
    if (!music.openFromFile("music/battle.mp3")) { return -1;}
    music.play();

    // A string describing the current situation of the fight (start of the fight, loss, victory, escape)
    string situation = ("The fight has begun. " + currDuel.first.getName() + " VS " + currDuel.second.getName());

    Clock animationClock;
    int currentFrameEnemy = 0;
    int currentFrameYour  = 0;
    bool run = false;

    int enemyFrameCount, enemyFrameWidth, enemyFrameHeight; // Enemy
    int yourFrameCount, yourFrameWidth, yourFrameHeight;    // You
    while (window.isOpen())
    {
        window.clear();

        Texture texture, animationTexture, animationTexture1;
        if (!texture.loadFromFile("img/battle_phon/forest2.png"))      { return 0; }  // The texture of the forest
        if (!animationTexture1.loadFromFile(currDuel.first.getPath())) { return 0; }  // The texture of your current PokeMon
        if (!animationTexture.loadFromFile(currDuel.second.getPath())) { return 0; }  // The texture ot enemy PokeMon

        Sprite sprite(texture);
        sprite.setTexture(texture);
        sprite.setScale((float)window.getSize().x / sprite.getLocalBounds().width, (float)window.getSize().y / sprite.getLocalBounds().height);
        sprite.setPosition(0, 0);
        window.draw(sprite);

        // Setting the texture of an enemy PokeMon
        enemyFrameCount = currDuel.second.getcFrame();
        enemyFrameWidth = currDuel.second.getWidth() / enemyFrameCount;
        enemyFrameHeight = currDuel.second.getHeight(); 

        Sprite animationEnemySprite(animationTexture);
        animationEnemySprite.setTextureRect(IntRect(0, 0, enemyFrameWidth, enemyFrameHeight));
        animationEnemySprite.setScale(3.0f, 3.0f);
        Vector2f newPosition1(enemyPositionX + 100, enemyPositionY + 50);
        animationEnemySprite.setOrigin(enemyFrameWidth / 2, enemyFrameHeight / 2);
        animationEnemySprite.setPosition(newPosition1.x, newPosition1.y);

        // Setting the texture of an нщгк PokeMon
        yourFrameCount = currDuel.first.getcFrame();
        yourFrameWidth = currDuel.first.getWidth() / yourFrameCount; 
        yourFrameHeight = currDuel.first.getHeight(); 

        Sprite animationYourSprite(animationTexture1);
        animationYourSprite.setScale(5.0f, 5.0f);
        animationYourSprite.setTextureRect(IntRect(0, 0, yourFrameWidth, yourFrameHeight));
        Vector2f newPosition(yourPositionX + 100, yourPositionY + 50);
        animationYourSprite.setOrigin(yourFrameWidth / 2, yourFrameHeight / 2);
        animationYourSprite.setPosition(newPosition.x, newPosition.y);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (animationClock.getElapsedTime().asSeconds() >= 1.5f) {
            currentFrameEnemy = (currentFrameEnemy + 1) % enemyFrameCount;
            animationEnemySprite.setTextureRect(IntRect(currentFrameEnemy * enemyFrameWidth, 0, enemyFrameWidth, enemyFrameHeight));
        }
        if (animationClock.getElapsedTime().asSeconds() >= 1.5f) {
            currentFrameYour = (currentFrameYour + 1) % yourFrameCount;
            animationYourSprite.setTextureRect(IntRect(currentFrameYour * yourFrameWidth, 0, yourFrameWidth, yourFrameHeight));
        }

        window.draw(animationEnemySprite);
        window.draw(animationYourSprite);

        drawField(window, currDuel, situation, typeMatrix, weatherCommand, run);
        window.display();

        // PokeMon (Yours or not) is defeated
        if (currDuel.first.getHealth() <= 0.0) {
            if (indexYou + 1 < list_of_op.first.size()) {
                indexYou++;
                currDuel.first = list_of_op.first[indexYou];
            }
            else {  // Loss
                situation = "Congratulations, you've lost!";
                currDuel.first.deleteComm(0);
                currDuel.second.deleteComm(1);
            }
        }

        if (currDuel.second.getHealth() <= 0.0) {
            if (indEnemy + 1 < list_of_op.second.size()) {
                indEnemy++;
                currDuel.second = list_of_op.second[indEnemy];
            }
            else {  // Win
                situation = "You have won! Bake a punching bag!";
            }
        }
    }
    return 0;
}
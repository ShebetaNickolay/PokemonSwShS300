#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "pokemon.h"
#include "command.h"
#include "field.h" 

#include <fstream>
#include <vector>
#include <string>

using namespace sf;
using namespace std;

int getRandomNumberN(int n) {
    return rand() % n;
}

vector<PCommand> create_list_of_commands() {
    ifstream file("txtFile/your_command_list.txt");
    vector<PCommand> result;

    double damage, healing;
    bool owner;
    int type;
    string name;

    for (int i = 0; i < 20; i++) {
        file >> damage >> healing >> owner >> type >> name;
        result.push_back(PCommand(damage, healing, owner, type, name));
    }
    file.close();
    return result;
}


vector<PokeMon> create_list_of_pokemon(vector<PCommand> &listOfCommands) {
    ifstream file("txtFile/pokemon_list.txt");
    vector<PokeMon> result;
    double health, attack, defense;
    bool owner;
    int type1, type2;
    string name;

    vector<PCommand> comm = { listOfCommands[getRandomNumberN(listOfCommands.size())], listOfCommands[getRandomNumberN(listOfCommands.size())],
    listOfCommands[getRandomNumberN(listOfCommands.size())], listOfCommands[getRandomNumberN(listOfCommands.size())] };

    for (int i = 0; i < 25; i++) {
        file >> health >> attack >> defense >> owner >> type1 >> type2 >> name;
        result.push_back(PokeMon(health, attack, defense, comm, owner, type1, type2, name));
    }
    file.close();
    return result;
}


pair<vector<PokeMon>, vector<PokeMon>> create_list(vector<PokeMon>& list_of_pok) {
    int n = list_of_pok.size();
    vector<PokeMon> first = { list_of_pok[getRandomNumberN(n)],
                              list_of_pok[getRandomNumberN(n)] ,
                              list_of_pok[getRandomNumberN(n)] ,
                              list_of_pok[getRandomNumberN(n)],
                              list_of_pok[getRandomNumberN(n)] ,
                              list_of_pok[getRandomNumberN(n)] };
    vector<PokeMon> second = { list_of_pok[getRandomNumberN(n)],
                              list_of_pok[getRandomNumberN(n)] ,
                              list_of_pok[getRandomNumberN(n)] ,
                              list_of_pok[getRandomNumberN(n)],
                              list_of_pok[getRandomNumberN(n)] ,
                              list_of_pok[getRandomNumberN(n)] };
    return make_pair(first, second);
}

int main() {
    vector<PCommand> commandList = create_list_of_commands();
    vector<PokeMon> pokemonList = create_list_of_pokemon(commandList);
    pair<vector<PokeMon>, vector<PokeMon>> list_of_op = create_list(pokemonList);

    int ind1 = 0, ind2 = 0;
    pair<PokeMon, PokeMon> tmp = { list_of_op.first[ind1], list_of_op.second[ind2] };
      
   // pair<vector<PokeMon>, vector<PokeMon>> battle_op = make_pair(create_your_team(), create_enemy_team());
    RenderWindow window(VideoMode(1600, 1000), "Pokemon. Galar forest battle.");

   //Music music;
   //if (!music.openFromFile("music/battle1.mp3"))
   //{
   //    return -1;
   //}

   //music.play();

   string situation = "The fight has begun. ";
   situation += tmp.first.getName();
   situation += " VS ";
   situation += tmp.second.getName();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        drawField(window, tmp, situation);
        window.display();

        if (tmp.first.getHealth() <= 0.0) {
            ind1++;
            tmp.first = list_of_op.first[ind1];
        }

        if (tmp.second.getHealth() <= 0.0) {
            ind2++;
            tmp.second = list_of_op.second[ind2];
        }
    }



    return 0;
}
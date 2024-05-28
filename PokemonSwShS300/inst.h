#include "pokemon.h"
#include "command.h"

#include <vector>
#include <string>
#include <fstream>

using namespace sf;
using namespace std;

// Creating a type matrix
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

// Creating a list of commands
vector<PCommand> create_list_of_commands() {
    ifstream file("txtFile/command_list.txt");
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

// Creating a PokeMon list
vector<PokeMon> create_list_of_pokemon(vector<PCommand>& listOfCommands, bool flag) {
    string nameF = (flag) ? ("txtFile/enemy_pokemon_list.txt") : ("txtFile/your_pokemon_list.txt");
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
                comm[i].owner = flag;   // 0 - You, 1 - Enemy
            }
            result.push_back(PokeMon(health, attack, defense, comm, type1, type2, name, cFrame, widthPic, heightPic));
        }
    }
    file.close();
    return result;
}

// Creating a squad list
pair<vector<PokeMon>, vector<PokeMon>> create_list(vector<PokeMon>& list_of_your_pok, vector<PokeMon>& list_of_enemy_pok) {
    int n = list_of_your_pok.size();
    int m = list_of_enemy_pok.size();
    vector<PokeMon> first = { list_of_your_pok[rand() % n],
    list_of_your_pok[rand() % n] ,list_of_your_pok[rand() % n] ,list_of_your_pok[rand() % n] ,list_of_your_pok[rand() % n] };

    for (int i = 0; i < first.size(); i++) {
        first[i].owner = 0;
    }
    vector<PokeMon> second = { list_of_enemy_pok[rand() % m],
                              list_of_enemy_pok[rand() % m],
                              list_of_enemy_pok[rand() % m],
                              list_of_enemy_pok[rand() % m],
                            list_of_enemy_pok[rand() % m] };
    for (int i = 0; i < second.size(); i++) {
        second[i].owner = 1;
    }
    return make_pair(first, second);
}


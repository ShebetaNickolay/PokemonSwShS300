#include <SFML/Graphics.hpp>
#include <vector> 
#include <string>
#include "Command.h"

using namespace std;

class PokeMon {
private: 
	int health;                // Здоровье
	vector<PCommand> moves;    // Список комманды
	bool owner;				   // Принадлежность ПокеМона, 0 - мой, 1 - чужой 
	int type1;				   // Первый тип ПокеМона
	int type2;                 // Второй тип ПокеМона
	string name;               // Наименование ПокеМона

public: 
	// Конструктор 
	PokeMon(int health, vector<PCommand> moves, bool owner, int type1, int type2, string name) :
		health(health), moves(moves), owner(owner), type1(type1), type2(type2), name(name) {};
	~PokeMon() {};

	string getPath() {
		string path = "img/";
		if (!owner) {
			path += "your_pokemon/";
		}
		else {
			path += "enemy_pokemon/";
		}

		path += (name + ".png");
		return path;
	}

	// Возвращение здоровья
	int getHealth()
	{
		return health;
	}

	// Возвращени списка комманд
	vector<PCommand> getMoves() {
		return moves;
	}

	// Возвращение принадлежности
	bool getOwner()
	{
		return owner;
	}

	// Возвращение типов ПокеМона
	pair<int, int> getTypes() {
		return make_pair(type1, type2);
	}

	// Возвращение наименование комманды
	string getName() {
		return name;
	}
	void takeDamage(int damage); // метод получения урона от вражеского Покемона 
	// void useMove(Pokemon* enemy); // метод нанесения урона врагу 
};
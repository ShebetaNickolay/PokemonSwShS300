#ifndef PokeMon_HEADER
#define PokeMon_HEADER

#include <SFML/Graphics.hpp>
#include <vector> 
#include <string>
#include "Command.h"

using namespace std;

class PokeMon {
private: 
	double health;                // Здоровье
	double attack;                // Базовый урон
	double defense;               // Защита
	vector<PCommand> moves;    // Список комманды
	int type1;				   // Первый тип ПокеМона
	int type2;                 // Второй тип ПокеМона
	string name;               // Наименование ПокеМона

	int cFrame;
	int width;
	int height;
	double beginHealth;
public: 
	bool owner = 0;				   // Принадлежность ПокеМона, 0 - мой, 1 - чужой 
	// Конструктор 
	PokeMon(double health, double attack, double defense, vector<PCommand> moves, 
		int type1, int type2, string name, int cFrame, int width, int height) :
		health(health), attack(attack), defense(defense), moves(moves),
		type1(type1), type2(type2), name(name), cFrame(cFrame), width(width), height(height)
	{
		beginHealth = health;
	};
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

	// Возвращение очков здоровья
	double getHealth() { return health; }

	// Возвращение базового урона
	double getAttack() { return attack;}

	// Возвращение очков защиты
	double getDefense() { return defense;}

	double getBegHealt() { return beginHealth; }
	// Возвращение списка комманд
	vector<PCommand> getMoves() { return moves;}

	// Возвращение принадлежности
	bool getOwner() { return owner; }

	// Возвращение типов ПокеМона
	pair<int, int> getTypes() {
		return make_pair(type1, type2);
	}

	int getcFrame() {
		return cFrame;
	}

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}

	void getHeal(double heal)
	{
		if (abs(heal - beginHealth) >= 1e6) {
			health += heal;
		}
	}
	// Возвращение наименование комманды
	string getName() { return name; }

	// метод получения урона от вражеского Покемона 
	void takeDamage(int damageOther) {
		(*this).health -= damageOther;
	}
	// void useMove(Pokemon* enemy); // метод нанесения урона врагу 
};

#endif
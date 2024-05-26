#ifndef PCommand_HEADER
#define PCommand_HEADER

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class PCommand {
private:
	double damage;		    // Урон
	double healing;        // Лечение
	int type;           // Тип команды
	bool owner;         // Принадлежность
	string name;        // Наименование команды
public:

	// Конструктор 
	PCommand(double damage, double healing, bool owner, int type, string name) :
		damage(damage), healing(healing), owner(owner), type(type), name(name) {};
	~PCommand() {};

	// Возвращение урона
	double getDamage() { return damage; }
	
	// Возвращение значения лечения
	double getHealing() { return healing;}

	// Возвращение типа команды
	int getTypeCom() { return type;}

	// Возвращение принадлежности
	bool getOwner() { return owner;}

	// Возвращение наименование команды
	string getName() { return name;}
};

#endif
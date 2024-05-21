#ifndef PCommand_HEADER
#define PCommand_HEADER

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class PCommand {
private:
	double damage;		    // Урон
	double healing;        // Лечение
	int type;           // Тип комманды
	bool owner;         // Принадлежность
	string name;        // Наименование комманды
public:

	// Конструктор 
	PCommand(double damage, double healing, bool owner, int type, string name) :
		damage(damage), healing(healing), owner(owner), type(type), name(name) {};
	~PCommand() {};

	// Возвращение урона
	double getDamage() { return damage; }
	
	// Возвращение значения лечения
	double getHealing() { return healing;}

	// Возвращение типа комманды
	int getTypeCom() { return type;}

	// Возвращение принадлежности
	bool getOwner() { return owner;}

	// Возвращение наименование комманды
	string getName() { return name;}
};

#endif
#ifndef PCommand_HEADER
#define PCommand_HEADER


#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class PCommand {
private:
	int damage;		    // Урон
	int healing;        // Лечение
	int type;           // Тип комманды
	string name;        // Наименование комманды
public:

	// Конструктор 
	PCommand(int damage, int healing, int type, string name) :
		damage(damage), healing(healing), type(type), name(name) {};
	~PCommand() {};

	// Возвращение урона
	int getDamage() 
	{ 
		return damage; 
	}
	
	// Возвращение значения лечения
	int getHealing() {
		return healing;
	}

	// Возвращение типа комманды
	int getType() 
	{ 
		return type; 
	}

	// Возвращение наименование комманды
	string getName() {
		return name;
	}
};

#endif
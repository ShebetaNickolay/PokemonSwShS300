#ifndef PokeMon_HEADER
#define PokeMon_HEADER

#include <SFML/Graphics.hpp>
#include <vector> 
#include <string>
#include "Command.h"

using namespace std;

class PokeMon {
private: 
	double health;                // ��������
	double attack;                // ������� ����
	double defense;               // ������
	vector<PCommand> moves;    // ������ ��������
	bool owner;				   // �������������� ��������, 0 - ���, 1 - ����� 
	int type1;				   // ������ ��� ��������
	int type2;                 // ������ ��� ��������
	string name;               // ������������ ��������

	double beginHealth;
public: 
	// ����������� 
	PokeMon(double health, double attack, double defense, vector<PCommand> moves, bool owner, int type1, int type2, string name) :
		health(health), attack(attack), defense(defense), moves(moves), owner(owner), type1(type1), type2(type2), name(name) {
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

	// ����������� ����� ��������
	double getHealth() { return health; }

	// ����������� �������� �����
	double getAttack() { return attack;}

	// ����������� ����� ������
	double getDefense() { return defense;}

	double getBegHealt() { return beginHealth; }
	// ����������� ������ �������
	vector<PCommand> getMoves() { return moves;}

	// ����������� ��������������
	bool getOwner() { return owner; }

	// ����������� ����� ��������
	pair<int, int> getTypes() {
		return make_pair(type1, type2);
	}

	// ����������� ������������ ��������
	string getName() { return name; }

	// ����� ��������� ����� �� ���������� �������� 
	void takeDamage(int damageOther) {
		(*this).health -= damageOther;
	}
	// void useMove(Pokemon* enemy); // ����� ��������� ����� ����� 
};

#endif
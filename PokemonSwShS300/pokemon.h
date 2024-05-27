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
	int type1;				   // ������ ��� ��������
	int type2;                 // ������ ��� ��������
	string name;               // ������������ ��������

	int cFrame;
	int width;
	int height;
	double beginHealth;
public: 
	bool owner = 0;				   // �������������� ��������, 0 - ���, 1 - ����� 
	// ����������� 
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
	// ����������� ������������ ��������
	string getName() { return name; }

	// ����� ��������� ����� �� ���������� �������� 
	void takeDamage(int damageOther) {
		(*this).health -= damageOther;
	}
	// void useMove(Pokemon* enemy); // ����� ��������� ����� ����� 
};

#endif
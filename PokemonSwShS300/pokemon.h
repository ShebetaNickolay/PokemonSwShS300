#include <SFML/Graphics.hpp>
#include <vector> 
#include <string>
#include "Command.h"

using namespace std;

class PokeMon {
private: 
	int health;                // ��������
	vector<PCommand> moves;    // ������ ��������
	bool owner;				   // �������������� ��������, 0 - ���, 1 - ����� 
	int type1;				   // ������ ��� ��������
	int type2;                 // ������ ��� ��������
	string name;               // ������������ ��������

public: 
	// ����������� 
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

	// ����������� ��������
	int getHealth()
	{
		return health;
	}

	// ���������� ������ �������
	vector<PCommand> getMoves() {
		return moves;
	}

	// ����������� ��������������
	bool getOwner()
	{
		return owner;
	}

	// ����������� ����� ��������
	pair<int, int> getTypes() {
		return make_pair(type1, type2);
	}

	// ����������� ������������ ��������
	string getName() {
		return name;
	}
	void takeDamage(int damage); // ����� ��������� ����� �� ���������� �������� 
	// void useMove(Pokemon* enemy); // ����� ��������� ����� ����� 
};
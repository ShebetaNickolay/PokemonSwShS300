#ifndef PCommand_HEADER
#define PCommand_HEADER

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class PCommand {
private:
	double damage;		    // ����
	double healing;        // �������
	int type;           // ��� �������
	string name;        // ������������ �������
	bool status; // 0 - ������� �����, 1 - ���������.

public:
	bool owner;         // ��������������
	// ����������� 
	PCommand(double damage, double healing, bool owner, int type, string name, bool status) :
		damage(damage), healing(healing), owner(owner), type(type), name(name), status(status) {};
	~PCommand() {};

	// ����������� �����
	double getDamage() { return damage; }
	
	// ����������� �������� �������
	double getHealing() { return healing;}

	// ����������� ���� �������
	int getTypeCom() { return type;}

	// ����������� ��������������
	bool getOwner() { return owner;}

	bool getStatus() { return status; }

	// ����������� ������������ �������
	string getName() { return name;}
};

#endif
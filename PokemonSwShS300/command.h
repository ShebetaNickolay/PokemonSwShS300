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
public:
	bool owner;         // ��������������
	// ����������� 
	PCommand(double damage, double healing, bool owner, int type, string name) :
		damage(damage), healing(healing), owner(owner), type(type), name(name) {};
	~PCommand() {};

	// ����������� �����
	double getDamage() { return damage; }
	
	// ����������� �������� �������
	double getHealing() { return healing;}

	// ����������� ���� �������
	int getTypeCom() { return type;}

	// ����������� ��������������
	bool getOwner() { return owner;}

	// ����������� ������������ �������
	string getName() { return name;}
};

#endif
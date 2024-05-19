#ifndef PCommand_HEADER
#define PCommand_HEADER


#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class PCommand {
private:
	int damage;		    // ����
	int healing;        // �������
	int type;           // ��� ��������
	string name;        // ������������ ��������
public:

	// ����������� 
	PCommand(int damage, int healing, int type, string name) :
		damage(damage), healing(healing), type(type), name(name) {};
	~PCommand() {};

	// ����������� �����
	int getDamage() 
	{ 
		return damage; 
	}
	
	// ����������� �������� �������
	int getHealing() {
		return healing;
	}

	// ����������� ���� ��������
	int getType() 
	{ 
		return type; 
	}

	// ����������� ������������ ��������
	string getName() {
		return name;
	}
};

#endif
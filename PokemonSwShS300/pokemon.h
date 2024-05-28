#ifndef PokeMon_HEADER
#define PokeMon_HEADER

#include <SFML/Graphics.hpp>
#include <vector> 
#include <string>
#include "Command.h"

using namespace std;

class PokeMon {
private: 
	double health;                // Health
	double attack;                // Base Damage
	double defense;               // Protection
	vector<PCommand> moves;		  // List of commands
	int type1;				      // The first type of PokeMon
	int type2;                    // The second type of PokeMon
	string name;                  // The name of the PokeMon
	int cFrame;				      // Number of frames
	int width;					  // Texture width
	int height;				      // Texture height
	double beginHealth;           // Base health
public: 
	bool owner = 0;				   //  0 - You, 1 - Enmey 
	PokeMon(double health, double attack, double defense, vector<PCommand> moves, 
		int type1, int type2, string name, int cFrame, int width, int height) :
		health(health), attack(attack), defense(defense), moves(moves),
		type1(type1), type2(type2), name(name), cFrame(cFrame), width(width), height(height)
	{
		beginHealth = health;
	};
	~PokeMon() {};

	// Creating a file path
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

	// Return of health points
	double getHealth() { return health; }

	// Return of base damage
	double getAttack() { return attack;}

	// Return of protection points
	double getDefense() { return defense;}

	// Return of base health points
	double getBegHealt() { return beginHealth; }

	// Returning the list of commands
	vector<PCommand> getMoves() { return moves;}

	// Return of the accessory
	bool getOwner() { return owner; }

	// The Return of Pokemon Types
	pair<int, int> getTypes() { return make_pair(type1, type2); }

	// Returning the number of frames
	int getcFrame() { return cFrame; }

	// Returning the width of the texture
	int getWidth() { return width; }

	//Returning the height of the texture
	int getHeight() { return height; }

	// The method of obtaining treatment
	void getHeal(double heal)
	{
		health += heal;

		// If the current health exceeds the baseline
		if (health > beginHealth) {
			health = beginHealth;
		}
	}

	// Returning the name of PokeMon
	string getName() { return name; }

	// The method of taking damage from an enemy PokeMon
	void takeDamage(int damageOther) {
		(*this).health -= damageOther;
	}

	// The method that blocks the game (the last Pokemon, yours or not, is dead)
	void deleteComm(bool flag) {
		for (int i = 0; i < moves.size(); i++) {
			moves[i].damage = 0;
			moves[i].healing = 0;
			if (flag) { // Enemy win 
				moves[i].name = "Enemy win";
			}
			else {     // Your loss or escape
				moves[i].name = "Defeated";
			}
		}
	}
};

#endif
#ifndef PCommand_HEADER
#define PCommand_HEADER

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

struct PCommand {
double damage;		    // Damage
	  double healing;   // Heal
	  int type;         // Type of command
	  string name;      // Name of the command
	  bool status;		// 0 is a normal attack, 1 is a status (weather) attack
	  bool owner;       // Affiliation

	  PCommand(double damage, double healing, bool owner, int type, string name, bool status) :
		damage(damage), healing(healing), owner(owner), type(type), name(name), status(status) {};

	  ~PCommand() {};

	  // Damage Return
	  double getDamage() { return damage; }
	
	  // Returning the value of the treatment
	  double getHealing() { return healing;}

	
	  // Returning the command type
	  int getTypeCom() { return type;}

	
	  // Return of the accessory
	  bool getOwner() { return owner;}

	
	  // Return of the status
	  bool getStatus() { return status; }

	  // Return the name of the command
	  string getName() { return name;}
};

#endif
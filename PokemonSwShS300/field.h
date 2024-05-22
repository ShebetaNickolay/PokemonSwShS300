#include <SFML/Graphics.hpp>

#include "button.h"
#include "pokemon.h"
#include "command.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;
using namespace sf;

const int LEVEL = 1;
const double EPS = 1e-6;

vector <vector<int>> colorTypeList = {
	{ 200, 200, 200},
	{ 255, 153,  51},
	{ 102, 178, 200},
	{  0, 204, 102},
	{ 255, 255,  51},
	{ 102, 255, 255},
	{ 255,   0,   0},
	{ 153,  51, 255},
	{ 204, 102,   0},
	{ 153, 255, 255},
	{ 255, 153, 255},
	{ 128, 255,   0},
	{ 153,  76,   0},
	{ 204, 153, 255},
	{ 76,   0, 153},
	{ 96,  96,  96},
	{ 202, 202, 202},
	{ 255, 204, 229},
};

std::string limitPrecision(double number, int precision) {
	std::ostringstream oss;
	oss.precision(precision);
	oss << std::fixed << number;
	return oss.str();
}

int getRandomNumber() {
	srand(time(0));
	return rand() % 4;
}

double enemyTakeDamage(pair<PokeMon, PokeMon> &tmp, PCommand &pcommand) {
	double coeff = 1.5;
	double yourArttack = (((2.0 * LEVEL / 5.0 + 2) * pcommand.getDamage() * tmp.first.getAttack() / 3.0) / 50.0 + 2) * coeff;
	double dmg = tmp.second.getDefense() - yourArttack;
	if (dmg <= 0.0) {
		tmp.second.takeDamage(-dmg);
		return dmg;
	}
	return 0.0;
};

double youTakeDamage(pair<PokeMon, PokeMon>& tmp, PCommand& pcommand) {
	double coeff = 1.5;
	double enemyArttack = (((2.0 * LEVEL / 5.0 + 2) * pcommand.getDamage() * tmp.second.getAttack() / 3.0) / 50.0 + 2) * coeff;
	double dmg = tmp.first.getDefense() - enemyArttack;
	if (dmg <= 0.0) {
		tmp.first.takeDamage(-dmg);
		return dmg;
	}

	return 0, 0;
};

string create_new_situation(pair<PokeMon, PokeMon>& tmp, double first, double second) {
	string res = "Your " + tmp.first.getName();
	res += (" dealt " + limitPrecision(abs(first), 2) + " points of damage. ");
	res += ("Enemy's " + tmp.second.getName());
	res += (" dealt " + limitPrecision(abs(second), 2) + " points of damage to you.\n");

	if (tmp.first.getHealth() <= 0.0) {
		res += ("Your PokeMon fell in battle.\n");
	}

	if (tmp.second.getHealth() <= 0.0) {
		res += ("The enemy Pokemon fell in battle");
	}
	return res;
}

void drawField(RenderWindow& window, pair<PokeMon, PokeMon> &tmp, string &situation) {

	vector<PCommand> list = tmp.first.getMoves();

	Texture texture; 
	if (!texture.loadFromFile("img/battle_phon/forest2.png")) { return; } 
	Sprite sprite(texture); 

	sprite.setTexture(texture); 
	sprite.setScale((float)window.getSize().x / sprite.getLocalBounds().width, 
		(float)window.getSize().y / sprite.getLocalBounds().height);
		
	sprite.setPosition(0, 0);

	// Âàø ÏîêåÌîí
	RectangleShape YouSquare(Vector2f(550, 550));
	YouSquare.setPosition(150, 375);

	// Âðàæåñêèé ÏîêåÌîí
	RectangleShape EnemySquare(Vector2f(250, 250));
	EnemySquare.setPosition(1125, 200);

	// Îñíîâíàÿ ÷àñòü äëÿ ìåíþ 
	RectangleShape MenuRectangle(Vector2f(550, 400));
	MenuRectangle.setPosition(1040, 585);
	MenuRectangle.setFillColor(Color(0, 140, 0)); // Òåìíî-çåëåíûé öâåò
	MenuRectangle.setOutlineColor(Color::Black);
	MenuRectangle.setOutlineThickness(5);

	// Óñòàíîâêà øðèôòà äëÿ òåêñòà
	Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setString(situation);
	text.setPosition(300, 10);

	// Çàãðóçêà èçîáðàæåíèÿ âàøåãî ïîêåìîíà
	Texture yourPokemonTexture;
	if (!yourPokemonTexture.loadFromFile(tmp.first.getPath())) {
		// Îøèáêà ïðè çàãðóçêå èçîáðàæåíèÿ
		return;
	}
	YouSquare.setTexture(&yourPokemonTexture);

	// Çàãðóçêà èçîáðàæåíèÿ äëÿ âðàæåñêîãî ÏîêåÌîíà
	Texture enemyPokemonTexture;
	if (!enemyPokemonTexture.loadFromFile(tmp.second.getPath())) {
		// Îøèáêà ïðè çàãðóçêå èçîáðàæåíèÿ
		return;
	}
	EnemySquare.setTexture(&enemyPokemonTexture);

	// Îòðèñîâêà âñåõ ýëåìåíòîâ
	window.draw(sprite);
	window.draw(YouSquare);
	window.draw(EnemySquare);
	window.draw(MenuRectangle);
	window.draw(text);

	// Ïðèåìû âàøåãî ÏîêåÌîíà
	Button firstButton(1050, 600, 250, 150, list[0].getName());
	firstButton.setColor(colorTypeList[list[0].getTypeCom()]);
	firstButton.drawButton(window);

	Button secondButton(1325, 600, 250, 150, list[1].getName());
	secondButton.setColor(colorTypeList[list[1].getTypeCom()]);
	secondButton.drawButton(window);

	Button thirdButton(1050, 800, 250, 150, list[2].getName());
	thirdButton.setColor(colorTypeList[list[2].getTypeCom()]);
	thirdButton.drawButton(window);
	
	Button fourthButton(1325, 800, 250, 150, list[3].getName());
	fourthButton.setColor(colorTypeList[list[3].getTypeCom()]);
	fourthButton.drawButton(window);

	// Êíîïêà ïîáåãà, âåðñèÿ 1
	Button Run(25, 25, 100, 50, "Run");
	Run.setColor(0, 204, 102);
	Run.drawButton(window);

	// Ïîëîñû çäðîâüÿ âàøåãî è âðàæåñêîãî Ïîêåìîíà
	Button yourHPline(725, 800, 250, 50, to_string(tmp.first.getHealth()));
	yourHPline.setColor(0, 153, 0); 
	if (tmp.first.getHealth() <= 0.0) {
		yourHPline.setColor(204, 0, 0);
	}
	yourHPline.drawButton(window);

	Button enemyHPline(850, 200, 250, 50, to_string(tmp.second.getHealth()));
	enemyHPline.setColor(0, 151, 0);
	if (tmp.second.getHealth() <= 0.0) {
		enemyHPline.setColor(204, 0, 0);
	}
	enemyHPline.drawButton(window);
	
	bool flag = false;
	double yourAttackStr = 0.0, enemyAttackStr = 0.0;
	// Îáðàáîòêà íàæàòèÿ íà êíîïêè ñ âûáîðîì êîìàíäû
	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (firstButton.isButtonHovered(mousePos)) {
			// Îáðàáîòêà íàæàòèÿ íà ïåðâóþ êíîïêó
			yourAttackStr = enemyTakeDamage(tmp, list[0]);
			flag = true;
			enemyAttackStr = 0.0;
		}
		else if (secondButton.isButtonHovered(mousePos)) {
			// Îáðàáîòêà íàæàòèÿ íà âòîðóþ êíîïêó
			yourAttackStr = enemyTakeDamage(tmp, list[1]);
			flag = true;
			enemyAttackStr = 0.0;
		}
		else if (thirdButton.isButtonHovered(mousePos)) {
			// Îáðàáîòêà íàæàòèÿ íà òðåòüþ êíîïêó
			yourAttackStr = enemyTakeDamage(tmp, list[2]);
			flag = true;
			enemyAttackStr = 0.0;
		}
		else if (fourthButton.isButtonHovered(mousePos)) {
			// Îáðàáîòêà íàæàòèÿ íà ÷åòâåðòóþ êíîïêó
			yourAttackStr = enemyTakeDamage(tmp, list[3]);
			flag = true;
			enemyAttackStr = 0.0;
		}
	}

	vector<PCommand> listEnemyCommand = tmp.second.getMoves();
	if (flag) {
		sleep(seconds(1));
		if (tmp.second.getHealth() > 0.0) {
			enemyAttackStr = youTakeDamage(tmp, listEnemyCommand[getRandomNumber()]);
			flag = false;
		}
		situation = create_new_situation(tmp, yourAttackStr, enemyAttackStr);
	}
}

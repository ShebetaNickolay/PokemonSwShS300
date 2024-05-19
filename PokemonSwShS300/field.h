#include <SFML/Graphics.hpp>
#include "button.h"
#include "pokemon.h"
#include "command.h"
#include <iostream>
#include <vector>

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


int getRandomNumber() {
	return rand() % 4;
}


void enemyTakeDamage(pair<PokeMon, PokeMon> &tmp, PCommand &pcommand) {
	double coeff = 1.5;
	double yourArttack = (((2.0 * LEVEL / 5.0 + 2) * pcommand.getDamage() * tmp.first.getAttack() / 3.0) / 50.0 + 2) * coeff;

	tmp.second.takeDamage(abs(tmp.second.getDefense() - yourArttack));
};

void youTakeDamage(pair<PokeMon, PokeMon>& tmp, PCommand& pcommand) {
	double coeff = 1.5;
	double enemyAttack = (((2.0 * LEVEL / 5.0 + 2) * pcommand.getDamage() * tmp.second.getAttack() / 3.0) / 50.0 + 2) * coeff;

	tmp.first.takeDamage(abs(tmp.first.getDefense() - enemyAttack));
};


void drawField(RenderWindow& window, pair<PokeMon, PokeMon> &tmp) {
	Texture texture; 
	if (!texture.loadFromFile("img/battle_phon/forest2.png")) { return; } 
	Sprite sprite(texture); 

	sprite.setTexture(texture); 
	sprite.setScale((float)window.getSize().x / sprite.getLocalBounds().width, 
		(float)window.getSize().y / sprite.getLocalBounds().height);
		
	sprite.setPosition(0, 0);

	// ��� �������
	RectangleShape YouSquare(Vector2f(550, 550));
	YouSquare.setPosition(150, 375);

	// ��������� �������
	RectangleShape EnemySquare(Vector2f(250, 250));
	EnemySquare.setPosition(1125, 200);

	// �������� ����� ��� ���� 
	RectangleShape MenuRectangle(Vector2f(550, 400));
	MenuRectangle.setPosition(1040, 585);
	MenuRectangle.setFillColor(Color(0, 140, 0)); // �����-������� ����
	MenuRectangle.setOutlineColor(Color::Black);
	MenuRectangle.setOutlineThickness(5);

	// ����������� ������� �������� / �������� �� ���� ���
	RectangleShape InfoRectangle(Vector2f(1000, 50));
	InfoRectangle.setPosition(300, 10);
	InfoRectangle.setFillColor(Color(0, 140, 0)); // �����-������� ����
	InfoRectangle.setOutlineColor(Color::Black);
	InfoRectangle.setOutlineThickness(5);
	
	// �������� ����������� ������ ��������
	Texture yourPokemonTexture;
	if (!yourPokemonTexture.loadFromFile(tmp.first.getPath())) {
		// ������ ��� �������� �����������
		return;
	}
	YouSquare.setTexture(&yourPokemonTexture);

	// �������� ����������� ��� ���������� ��������
	Texture enemyPokemonTexture;
	if (!enemyPokemonTexture.loadFromFile(tmp.second.getPath())) {
		// ������ ��� �������� �����������
		return;
	}
	EnemySquare.setTexture(&enemyPokemonTexture);

	// ��������� ���� ���������
	window.draw(sprite);
	window.draw(YouSquare);

	window.draw(EnemySquare);
	window.draw(MenuRectangle);
	window.draw(InfoRectangle);

	vector<PCommand> list = tmp.first.getMoves();

	// ������ ������ ��������
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

	Button Run(25, 25, 100, 50, "Run");
	Run.setColor(0, 0, 255);
	Run.drawButton(window);

	Button yourHPline(725, 800, 250, 50, to_string(tmp.first.getHealth()));
	yourHPline.setColor(0, 255, 0); 
	yourHPline.drawButton(window);

	Button enemyHPline(850, 200, 250, 50, to_string(tmp.second.getHealth()));
	enemyHPline.setColor(0, 255, 0);
	enemyHPline.drawButton(window);

	// ��������� ������� �� ������ � ������� �������
	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (firstButton.isButtonHovered(mousePos)) {
			// ��������� ������� �� ������ ������
			enemyTakeDamage(tmp, list[0]);
		}
		else if (secondButton.isButtonHovered(mousePos)) {
			// ��������� ������� �� ������ ������
			enemyTakeDamage(tmp, list[1]);
		}
		else if (thirdButton.isButtonHovered(mousePos)) {
			// ��������� ������� �� ������ ������
			enemyTakeDamage(tmp, list[2]);
		}
		else if (fourthButton.isButtonHovered(mousePos)) {
			// ��������� ������� �� ��������� ������
			enemyTakeDamage(tmp, list[3]);
		}
	}

}
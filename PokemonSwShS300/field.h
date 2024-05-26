#include <SFML/Graphics.hpp>

#include "button.h"
#include "pokemon.h"
#include "command.h"
#include "hpline.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
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

string limitPrecision(double number, int precision) {
	std::ostringstream oss;
	oss.precision(precision);
	oss << std::fixed << number;
	return oss.str();
}

int getRandomNumber() {
	srand(time(NULL));
	return rand() % 4;
}

double enemyTakeDamage(pair<PokeMon, PokeMon> &tmp, PCommand &pcommand, vector<vector<double>>& typeMatrix) {
	double coeff = abs(typeMatrix[pcommand.getTypeCom()][tmp.second.getTypes().first] + typeMatrix[pcommand.getTypeCom()][tmp.second.getTypes().second]);
	double yourArttack = (((2.0 * LEVEL / 5.0 + 2) * pcommand.getDamage() * tmp.first.getAttack() / 3.0) / 50.0 + 2) * coeff;
	double dmg = tmp.second.getDefense() - yourArttack;
	if (dmg <= 0.0) {
		tmp.second.takeDamage(-dmg);
		return dmg;
	}
	return 0.0;
};

double youTakeDamage(pair<PokeMon, PokeMon>& tmp, PCommand& pcommand, vector<vector<double>>& typeMatrix) {
	double coeff = abs(typeMatrix[pcommand.getTypeCom()][tmp.first.getTypes().first] + typeMatrix[pcommand.getTypeCom()][tmp.first.getTypes().second]);
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

void drawField(RenderWindow& window, pair<PokeMon, PokeMon> &tmp, string &situation, vector<vector<double>> &typeMatrix) {

	vector<PCommand> list = tmp.first.getMoves();

	// Основная часть для меню 
	RectangleShape MenuRectangle(Vector2f(475, 310));
	MenuRectangle.setPosition(1115, 680);
	MenuRectangle.setFillColor(Color(0, 140, 0)); // Темно-зеленый цвет
	MenuRectangle.setOutlineColor(Color::Black);
	MenuRectangle.setOutlineThickness(5);

	// Установка шрифта для текста
	Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setString(situation);
	text.setPosition(300, 10);

	// Отрисовка всех элементов

	window.draw(MenuRectangle);
	window.draw(text);

	// Приемы вашего ПокеМона
	Button firstButton(1125, 700, 450, 50, list[0].getName());
	firstButton.setColor(colorTypeList[list[0].getTypeCom()]);
	firstButton.drawButton(window);

	Button secondButton(1125, 775, 450, 50, list[1].getName());
	secondButton.setColor(colorTypeList[list[1].getTypeCom()]);
	secondButton.drawButton(window);

	Button thirdButton(1125, 850, 450, 50, list[2].getName());
	thirdButton.setColor(colorTypeList[list[2].getTypeCom()]);
	thirdButton.drawButton(window);
	
	Button fourthButton(1125, 925, 450, 50, list[3].getName());
	fourthButton.setColor(colorTypeList[list[3].getTypeCom()]);
	fourthButton.drawButton(window);

	// Кнопка побега, версия 1
	Button Run(25, 25, 100, 50, "Run");
	Run.setColor(0, 204, 102);
	Run.drawButton(window);

double num1 = tmp.first.getHealth(), num2 = tmp.second.getHealth();
std::stringstream stream, stream2;
stream << std::fixed << std::setprecision(2) << num1;
stream2 << std::fixed << std::setprecision(2) << num2;
std::string str1 = stream.str();
std::string str2 = stream2.str();
	
// Полосы здровья вашего и вражеского Покемона
HPLine yourHPline(725, 800, 250, 50, str1, tmp.first.getBegHealt());
if (tmp.first.getHealth() <= 0.0) {
    yourHPline.setColor(204, 0, 0);
}
yourHPline.drawButton(window);

HPLine enemyHPline(850, 200, 250, 50, str2, tmp.first.getBegHealt());
if (tmp.second.getHealth() <= 0.0) {
    enemyHPline.setColor(204, 0, 0);
}
enemyHPline.drawButton(window);

	
	bool flag = false;
	double yourAttackStr = 0.0, enemyAttackStr = 0.0;
	// Обработка нажатия на кнопки с выбором команды
	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (firstButton.isButtonHovered(mousePos)) {
			// Обработка нажатия на первую кнопку
			yourAttackStr = enemyTakeDamage(tmp, list[0], typeMatrix);
			flag = true;
			enemyAttackStr = 0.0;
		}
		else if (secondButton.isButtonHovered(mousePos)) {
			// Обработка нажатия на вторую кнопку
			yourAttackStr = enemyTakeDamage(tmp, list[1], typeMatrix);
			flag = true;
			enemyAttackStr = 0.0;
		}
		else if (thirdButton.isButtonHovered(mousePos)) {
			// Обработка нажатия на третью кнопку
			yourAttackStr = enemyTakeDamage(tmp, list[2], typeMatrix);
			flag = true;
			enemyAttackStr = 0.0;
		}
		else if (fourthButton.isButtonHovered(mousePos)) {
			// Обработка нажатия на четвертую кнопку
			yourAttackStr = enemyTakeDamage(tmp, list[3], typeMatrix);
			flag = true;
			enemyAttackStr = 0.0;
		}
		else if (fourthButton.isButtonHovered(mousePos)) {
			
		}
	}

	vector<PCommand> listEnemyCommand = tmp.second.getMoves();
	if (flag) {
		sleep(seconds(1));
		if (tmp.second.getHealth() > 0.0) {
			enemyAttackStr = youTakeDamage(tmp, listEnemyCommand[getRandomNumber()], typeMatrix);
			flag = false;
		}
		situation = create_new_situation(tmp, yourAttackStr, enemyAttackStr);
	}
}
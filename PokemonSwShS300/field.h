#include <SFML/Graphics.hpp>
#include "button.h"
#include "pokemon.h"
#include "command.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

void info(PokeMon your) {
	cout << "��� ��������: " << your.getName() << '\n';
	cout << "���� ��������: " << your.getTypes().first << ' ' << your.getTypes().second << '\n';
	cout << "��������������: " << your.getOwner() << '\n';
	vector<PCommand> list = your.getMoves();
	for (int i = 0; i < list.size(); i++) {
		cout << list[i].getName() << '\n';
	}
}

pair<PokeMon, PokeMon> create(){
	vector<PCommand> yourList, enemyList;

	yourList.push_back(PCommand(50, 0, 1, "Arm Thrust"));
	yourList.push_back(PCommand(25, 0, 2, "Body Press"));
	yourList.push_back(PCommand(150, 0, 1, "Close Combatt"));
	yourList.push_back(PCommand(0, 100, 2, "Arm Thrust"));

	enemyList.push_back(PCommand(75, 0, 3, "Aqua Jet"));
	enemyList.push_back(PCommand(25, 25, 4, "G-Max Cannonade"));
	enemyList.push_back(PCommand(100, 0, 3, "G-Max Foam Burst"));
	enemyList.push_back(PCommand(0, 150, 4, "Razor Shell"));

	PokeMon your  = PokeMon(300, yourList, 0, 1, 2, "Snom");
	PokeMon enemy = PokeMon(250, enemyList, 1, 3, 4, "Sobble");

	info(your);


	return make_pair(your, enemy);
}

void drawField(RenderWindow& window) {
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

	// ������ �������� �������� ������ ��������
	RectangleShape YouHP(Vector2f(250, 50));
	YouHP.setPosition(725, 800);

	// ��������� �������
	RectangleShape EnemySquare(Vector2f(250, 250));
	EnemySquare.setPosition(1125, 200);

	// ������ �������� ���������� ��������
	RectangleShape EnemyHP(Vector2f(250, 50));
	EnemyHP.setPosition(850, 200);

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
	
	pair<PokeMon, PokeMon> tmp = create();
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
	window.draw(YouHP);
	window.draw(EnemySquare);
	window.draw(EnemyHP);
	window.draw(MenuRectangle);
	window.draw(InfoRectangle);

	// ������ ������ ��������
	Button firstButton(1050, 600, 250, 150, "First");
	firstButton.setColor(255, 255, 255); // ������������� ����� ����
	firstButton.drawButton(window);

	Button secondButton(1325, 600, 250, 150, "Second");
	secondButton.setColor(255, 0, 0); // ������������� ����� ����
	secondButton.drawButton(window);

	Button thirdButton(1050, 800, 250, 150, "Third");
	thirdButton.setColor(0, 255, 0); // ������������� ����� ����
	thirdButton.drawButton(window);
	
	Button fourthButton(1325, 800, 250, 150, "Fourth");
	fourthButton.setColor(0, 0, 255); // ������������� ����� ����
	fourthButton.drawButton(window);

	Button Run(25, 25, 100, 50, "Run");
	Run.setColor(0, 0, 255); // ������������� ����� ����
	Run.drawButton(window);


}
#include <SFML/Graphics.hpp>
#include "button.h"

using namespace sf;
void drawField(sf::RenderWindow& window) {
	Texture texture; 
	if (!texture.loadFromFile("img/battle_phon/forest2.png")) 
	{ // Ошибка при загрузке текстуры
		return; } 
	Sprite sprite(texture); 

	sprite.setTexture(texture); 
	sprite.setScale((float)window.getSize().x / sprite.getLocalBounds().width, 
		(float)window.getSize().y / sprite.getLocalBounds().height);
		
	sprite.setPosition(0, 0);

	// Ваш ПокеМон
	RectangleShape YouSquare(Vector2f(550, 550));
	YouSquare.setPosition(150, 375);

	// Полоса здоровья текущего вашего ПокеМона
	RectangleShape YouHP(Vector2f(250, 50));
	YouHP.setPosition(725, 800);

	// Вражеский ПокеМон
	RectangleShape EnemySquare(Vector2f(250, 250));
	EnemySquare.setPosition(1125, 200);

	// Полоса здоровья варжеского ПокеМона
	RectangleShape EnemyHP(Vector2f(250, 50));
	EnemyHP.setPosition(850, 200);

	// Основная часть для меню 
	RectangleShape MenuRectangle(Vector2f(550, 400));
	MenuRectangle.setPosition(1040, 585);
	MenuRectangle.setFillColor(Color(0, 140, 0)); // Темно-зеленый цвет
	MenuRectangle.setOutlineColor(Color::Black);
	MenuRectangle.setOutlineThickness(5);

	// Отображение текущей операции / ситуации на поле боя
	RectangleShape InfoRectangle(Vector2f(1000, 50));
	InfoRectangle.setPosition(300, 10);
	InfoRectangle.setFillColor(Color(0, 140, 0)); // Темно-зеленый цвет
	InfoRectangle.setOutlineColor(Color::Black);
	InfoRectangle.setOutlineThickness(5);
	

	Texture yourPokemonTexture;
	if (!yourPokemonTexture.loadFromFile("img/enemy_pokemon/sobble.png")) {
		// Ошибка при загрузке изображения
		return;
	}
	YouSquare.setTexture(&yourPokemonTexture);

	// Загрузка изображения для вражеского ПокеМона
	Texture enemyPokemonTexture;
	if (!enemyPokemonTexture.loadFromFile("img/enemy_pokemon/snom.png")) {
		// Ошибка при загрузке изображения
		return;
	}
	EnemySquare.setTexture(&enemyPokemonTexture);

	// Отрисовка всех элементов
	window.draw(sprite);
	window.draw(YouSquare);
	window.draw(YouHP);
	window.draw(EnemySquare);
	window.draw(EnemyHP);
	window.draw(MenuRectangle);
	window.draw(InfoRectangle);

	// Приемы вашего ПокеМона
	Button firstButton(1050, 600, 250, 150, "First");
	firstButton.setColor(255, 255, 255); // устанавливаем белый цвет
	firstButton.drawButton(window);

	Button secondButton(1325, 600, 250, 150, "Second");
	secondButton.setColor(255, 0, 0); // устанавливаем белый цвет
	secondButton.drawButton(window);

	Button thirdButton(1050, 800, 250, 150, "Third");
	thirdButton.setColor(0, 255, 0); // устанавливаем белый цвет
	thirdButton.drawButton(window);
	
	Button fourthButton(1325, 800, 250, 150, "Fourth");
	fourthButton.setColor(0, 0, 255); // устанавливаем белый цвет
	fourthButton.drawButton(window);

	Button Run(25, 25, 100, 50, "Run");
	Run.setColor(0, 0, 255); // устанавливаем белый цвет
	Run.drawButton(window);


}
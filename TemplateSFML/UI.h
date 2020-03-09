#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Game.h"
class UI
{
public: 
	sf::RectangleShape* UIRectangle;
	sf::Text* vie;
	std::list<sf::CircleShape*> listVies;
	sf::Text* selectedWeapon;
	sf::RenderWindow* window;
	sf::Font* fontForText;
	Game* game;

public:
	UI(sf::RenderWindow* window, sf::String fontForText, Game* game);
	void DisplayUI();
	void UpdateHpPlayerUI();
	void UpdatePosUI();
};


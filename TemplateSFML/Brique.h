#pragma once
#include <SFML/Graphics.hpp>

enum class SensBrique { HORIZONTAL, VERTICAL };

class Brique
{
public:
	int posX;
	int posY;
	int width;
	SensBrique sensBrique;
	sf::RectangleShape rectangle;

public:
	Brique(int x, int y, SensBrique sens, int _thicknessesBrique, int width);
	void DisplayBrique(sf::RenderWindow* window);
};
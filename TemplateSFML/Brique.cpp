#include "Brique.h"
#include <SFML/Graphics.hpp>

Brique::Brique(int x, int y, SensBrique sens, int _thicknessesBrique, int _width) : posX(x), posY(y), sensBrique(sens), width(_width) {

	this->rectangle.setPosition(x, y);
	this->rectangle.setFillColor(sf::Color::Red);
	if (sens == SensBrique::HORIZONTAL) {
		this->rectangle.setSize(sf::Vector2f(_thicknessesBrique, width));
	}
	else {
		this->rectangle.setSize(sf::Vector2f(width, _thicknessesBrique));
	}

}

void Brique::DisplayBrique(sf::RenderWindow* window)
{
	window->draw(this->rectangle);
}
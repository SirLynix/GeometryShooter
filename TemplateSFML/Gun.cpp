#include "Gun.h"

Gun::Gun() : Weapon(1, 1.5f, .75f, -1, "Gun", 0.1f, 1.5f) {
	this->widthWeapon = 10;
	this->heightWeapon = 20;

	this->rectangle.setSize(sf::Vector2f(widthWeapon, heightWeapon));
	this->rectangle.setOrigin(sf::Vector2f(widthWeapon / 2, heightWeapon / 2));
	this->rectangle.setPosition(sf::Vector2f(this->origin.x, this->origin.y));
	this->rectangle.setFillColor(sf::Color(250, 16, 0));
}
#include "MachineGun.h"

MachineGun::MachineGun() : Weapon(1, 2.0f, 0.1f) {
	this->widthWeapon = 10;
	this->heightWeapon = 35;

	this->rectangle.setSize(sf::Vector2f(widthWeapon, heightWeapon));
	this->rectangle.setOrigin(sf::Vector2f(widthWeapon / 2, heightWeapon / 2));
	this->rectangle.setPosition(sf::Vector2f(this->origin.x, this->origin.y));
	this->rectangle.setFillColor(sf::Color::Red);
}
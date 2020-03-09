#include "MachineGun.h"

<<<<<<< HEAD
MachineGun::MachineGun() : Weapon(1, 2.0f, 0.1f, 100) {
=======
MachineGun::MachineGun() : Weapon(1, 2.0f, 0.1f, "Machinegun") {
>>>>>>> 34bbd960e3a27360bd77ee6bc29e1f34a5244e87
	this->widthWeapon = 10;
	this->heightWeapon = 35;

	this->rectangle.setSize(sf::Vector2f(widthWeapon, heightWeapon));
	this->rectangle.setOrigin(sf::Vector2f(widthWeapon / 2, heightWeapon / 2));
	this->rectangle.setPosition(sf::Vector2f(this->origin.x, this->origin.y));
	this->rectangle.setFillColor(sf::Color::Red);
}
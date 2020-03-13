#include "Archer.h"

Archer::Archer(float _posX, float _posY, int thicknessesEnemy, Weapon* weapon) : Enemy(_posX, _posY, thicknessesEnemy, weapon, 3, 0.0f) {
	this->rectangle.setFillColor(sf::Color::Cyan);

	this->weapon->cooldownFirerate = (float)(rand() % ((int)this->weapon->fireRate * 100)) / 100.0f;

	this->pv1.setSize(sf::Vector2f(thicknessesEnemy / 4, 5));
	this->pv1.setOrigin(this->pv1.getSize().x / 2, this->pv1.getSize().y / 2);
	this->pv1.setFillColor(sf::Color::Green);

	this->pv2.setSize(sf::Vector2f(thicknessesEnemy / 4, 5));
	this->pv2.setOrigin(this->pv2.getSize().x / 2, this->pv2.getSize().y / 2);
	this->pv2.setFillColor(sf::Color::Green);

	this->pv3.setSize(sf::Vector2f(thicknessesEnemy / 4, 5));
	this->pv3.setOrigin(this->pv3.getSize().x / 2, this->pv3.getSize().y / 2);
	this->pv3.setFillColor(sf::Color::Green);
}
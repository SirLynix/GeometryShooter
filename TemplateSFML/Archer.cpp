#include "Archer.h"

Archer::Archer(float _posX, float _posY, int thicknessesEnemy, Weapon* weapon) : Enemy(_posX, _posY, thicknessesEnemy, weapon) {
	this->rectangle.setFillColor(sf::Color::Cyan);
}
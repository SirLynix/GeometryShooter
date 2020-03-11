#include "Zombie.h"
#include "Character.h"

Zombie::Zombie(float _posX, float _posY, int thicknessesEnemy, Weapon* weapon) : Enemy(_posX, _posY, thicknessesEnemy, weapon, 3, 2.5f) {
	this->rectangle.setFillColor(sf::Color::Blue);

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

void Zombie::PerformAction(float _deltaTime)
{
	if (this->moveOnX) {
		this->MoveTo(this->speed * _deltaTime * 100 * GetNextMovementX(), 0);
	}
	if (this->moveOnY) {
		this->MoveTo(0, this->speed * _deltaTime * 100 * GetNextMovementY());
	}
}

float Zombie::GetNextMovementX()
{
	float moveX = 0;

	float dist = sqrt(pow(this->target.x - this->posX, 2) + pow(this->target.y - this->posY, 2));

	if (dist > 20.f) {

		double angle = atan2(this->target.y - this->posY, this->target.x - this->posX);

		moveX = cos(angle);
	}

	return moveX;
}

float Zombie::GetNextMovementY()
{
	float moveY = 0;

	float dist = sqrt(pow(this->target.x - this->posX, 2) + pow(this->target.y - this->posY, 2));

	if (dist > 20.f) {

		double angle = atan2(this->target.y - this->posY, this->target.x - this->posX);

		moveY = sin(angle);
	}
	return moveY;
}
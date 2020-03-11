#include "Zombie.h"
#include "Character.h"

Zombie::Zombie(float _posX, float _posY, int thicknessesEnemy, Weapon* weapon) : Enemy(_posX, _posY, thicknessesEnemy, weapon) {
	this->rectangle.setFillColor(sf::Color::Blue);
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
#include "Character.h"

Character::Character(int _vie, float _speed, float _posX, float _posY, bool _isEnemy, Weapon* weapon) : vie(_vie), speed(_speed), posX(_posX), posY(_posY), isEnemy(_isEnemy), weapon(weapon) {}

void Character::MoveTo(float _posX, float _poxY) {
	this->posX += _posX;
	this->posY += _poxY;
}

void Character::TakeDommage(int _dommage) {

	this->vie -= _dommage;
}

void Character::SetSpeed(float _speed) {
	this->speed = _speed;
}

void Character::FeedbackDamageTaken(float _deltaTime)
{

}
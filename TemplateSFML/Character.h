#pragma once
#include "Weapon.h"
class Character
{
public:
	int vie;
	float speed;
	float posX;
	float posY;
	bool isEnemy;
	Weapon* weapon;
public:
	Character(int _vie, float _speed, float _posX, float _posY, bool _isEnemy, Weapon* weapon);
	virtual void MoveTo(float _posX, float _poxY);
	void TakeDommage(int _dommage);
	void SetSpeed(float _speed);
};
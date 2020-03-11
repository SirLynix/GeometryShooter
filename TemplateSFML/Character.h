#pragma once
#include "Weapon.h"
class Character
{
public:
	int vie;
	float speed;
	float posX;
	float posY;
	float colorChangeDamage = 0.1f;
	bool isInvincible = false;
	bool isEnemy;
	bool hasTakenDamage = false;
	Weapon* weapon;
public:
	Character(int _vie, float _speed, float _posX, float _posY, bool _isEnemy, Weapon* weapon);
	virtual void MoveTo(float _posX, float _poxY);
	void TakeDommage(int _dommage);
	void SetSpeed(float _speed);
	virtual void FeedbackDamageTaken(float _deltaTime);
};
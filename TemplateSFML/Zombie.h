#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Weapon.h"

class Zombie : public Enemy
{
public:
	Zombie(float _posX, float _posY, int thicknessesEnemy, Weapon* weapon);
	void PerformAction(float _deltaTime) override;
	float GetNextMovementX();
	float GetNextMovementY();
};
#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Archer : public Enemy
{
public:
	Archer(float _posX, float _posY, int thicknessesEnemy, Weapon* weapon);
};
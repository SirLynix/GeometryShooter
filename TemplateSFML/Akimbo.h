#pragma once
#include "PowerUp.h"
class Akimbo : public PowerUp
{
public:
	Akimbo(float posX, float posY);
	void ApplyPowerUp(Player* player) override;
};


#pragma once
#include "PowerUp.h"
class Heal : public PowerUp
{
public:
	Heal(float posX, float posY, int _powerUp);
	void ApplyPowerUp(Player* player) override;
};

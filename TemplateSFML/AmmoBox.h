#pragma once
#include "PowerUp.h"
class AmmoBox : public PowerUp
{
public:
	AmmoBox(float posX, float posY);
	void ApplyPowerUp(Player* player) override;
};

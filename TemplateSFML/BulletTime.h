#pragma once
#include "PowerUp.h"

class BulletTime : public PowerUp
{
public:
	BulletTime(float posX, float posY, sf::Font* textFont, int _powerUp);
	void ApplyPowerUp(Player* player) override;
};


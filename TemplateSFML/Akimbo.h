#pragma once
#include "PowerUp.h"
class Akimbo : public PowerUp
{
public:
	Akimbo(float posX, float posY, sf::Font* font);
	void ApplyPowerUp(Player* player) override;
};


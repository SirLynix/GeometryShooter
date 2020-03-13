#include "Heal.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

Heal::Heal(float posX, float posY, int _powerUp) : PowerUp(posX, posY, "Heal", _powerUp) {

	this->namePowerUp.setPosition(this->posX - 20, this->posY - 45);
	this->namePowerUp.setCharacterSize(20);
}

void Heal::ApplyPowerUp(Player* player)
{
	player->vie += this->powerUp;
}

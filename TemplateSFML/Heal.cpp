#include "Heal.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

Heal::Heal(float posX, float posY, sf::Font* font, int _powerUp) : PowerUp(posX, posY, font, "Heal", _powerUp) {

	this->namePowerUp.setPosition(this->posX - 20, this->posY - 45);
	this->namePowerUp.setCharacterSize(20);
}

void Heal::ApplyPowerUp(Player* player)
{
	if (player->vie < 3) {
		player->vie += this->powerUp;
	}
}

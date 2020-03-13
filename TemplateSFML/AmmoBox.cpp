#include "AmmoBox.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

AmmoBox::AmmoBox(float posX, float posY, sf::Font* font) : PowerUp(posX, posY, font, "AmmoBox", 0) {
	this->namePowerUp.setPosition(this->posX - 50, this->posY - 45);
	this->namePowerUp.setCharacterSize(20);
}

void AmmoBox::ApplyPowerUp(Player* player)
{
	player->weapon->ammo = player->weapon->maxAmmo;

	if (player->isAkimbo)
		player->akimbo->ammo = player->weapon->maxAmmo;
}

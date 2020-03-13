#include "Akimbo.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

Akimbo::Akimbo(float posX, float posY, sf::Font* font) : PowerUp(posX, posY, font, "Akimbo", 0) {
	this->namePowerUp.setPosition(this->posX - 40, this->posY - 45);
	this->namePowerUp.setCharacterSize(20);
}

void Akimbo::ApplyPowerUp(Player* player)
{
	if (!player->isAkimbo) {
		player->isAkimbo = true;
		player->akimboCD = 5.f;
		player->akimbo = player->weapon->Clone();
	}
}

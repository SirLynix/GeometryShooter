#include "Heal.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

Heal::Heal(float posX, float posY, sf::Font textFont, int _powerUp) : PowerUp(posX, posY, "Heal", textFont,_powerUp){}

void Heal::ApplyPowerUp(Player* player)
{
	player->vie += this->powerUp;
}

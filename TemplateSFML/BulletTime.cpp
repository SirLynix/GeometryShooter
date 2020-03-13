#include "BulletTime.h"
#include "Player.h"

BulletTime::BulletTime(float posX, float posY, sf::Font* textFont, int timeBulletTime) : PowerUp(posX, posY, textFont, "BulletTime", timeBulletTime) {

	this->namePowerUp.setPosition(this->posX - 60, this->posY - 45);
	this->namePowerUp.setCharacterSize(20);
}

void BulletTime::ApplyPowerUp(Player* player)
{
	player->bulletTimeDuration = this->powerUp;
	player->onBulletTime = true;
}
#include "PowerUp.h"

const float radiusPowerUp = 25.0f;

PowerUp::PowerUp(float _posX, float _posY, std::string _namePowerUp, sf::Font& fontText, float _powerUp) : posX(_posX), posY(_posY), powerUp(_powerUp)
{
	this->circle.setPosition(sf::Vector2f(this->posX, this->posY));
	this->circle.setRadius(radiusPowerUp);
	this->circle.setOrigin(sf::Vector2f(radiusPowerUp, radiusPowerUp));

	this->namePowerUp.setPosition(sf::Vector2f(this->posX, this->posY));
	this->namePowerUp.setString(sf::String(_namePowerUp));
	this->namePowerUp.setFont(fontText);
}

void PowerUp::ApplyPowerUp(Player* player) {}

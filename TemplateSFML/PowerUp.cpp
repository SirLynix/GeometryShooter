#include "PowerUp.h"

const float radiusPowerUp = 15.0f;

PowerUp::PowerUp(float _posX, float _posY, std::string _namePowerUp, float _powerUp) : posX(_posX), posY(_posY), powerUp(_powerUp)
{
	this->circle.setRadius(radiusPowerUp);
	this->circle.setOrigin(sf::Vector2f(radiusPowerUp, radiusPowerUp));
	this->circle.setPosition(sf::Vector2f(this->posX, this->posY));

	this->namePowerUp.setString(sf::String(_namePowerUp));
	this->namePowerUp.setPosition(sf::Vector2f(this->posX, this->posY));
}

void PowerUp::ApplyPowerUp(Player* player) {}

void PowerUp::DisplayPowerUp(sf::RenderWindow* window)
{
	window->draw(this->circle);
	window->draw(this->namePowerUp);
}

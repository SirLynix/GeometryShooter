#pragma once
#include <SFML/Graphics.hpp>
class Player;

class PowerUp
{
public:
	float posX;
	float posY;
	float powerUp;
	sf::CircleShape circle;
	sf::Text namePowerUp;
public:
	PowerUp(float _posX, float _posY, std::string namePowerUp, float _powerUp);
	virtual void ApplyPowerUp(Player* player);
	void DisplayPowerUp(sf::RenderWindow* window);
};


#pragma once
#include "SFML/Graphics.hpp"

class ShakeScreen
{
public:
	float timeShake;
	bool shakeSreen;
	float amplitude;
	sf::View* viewOfGame;
	sf::Vector2f originePLayer;
private :
	float coolDownShake;

public:
	ShakeScreen(sf::View* _viewOfGame, sf::Vector2f _originePLayer);
	void UpdateOrigine(sf::Vector2f _originePLayer);
	void CheckForShake();
	void Shake();
	void UpdateCooldown(float deltaTime);
	void UpdateAmplitude(float amplitude);
	void UpdateTimeShake(float timeShake);
};


#pragma once
#include "GrenadeLauncher.h"
#include <SFML/Audio.hpp>
class Grenade : public Projectile
{
public: 
	sf::CircleShape shockWave;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	bool canPlay = true;

public:
	Grenade(sf::Vector2f origin, sf::Vector2f targetProjectile, PROJECTILE_OF projectileOf, sf::Color colorProjectil);
	void MoveProjectile(float _deltaTime);
	void SetExplosionSettings();
};


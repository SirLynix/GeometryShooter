#pragma once
#include "GrenadeLauncher.h"
class Grenade : public Projectile
{
public: 
	sf::CircleShape shockWave;
public:
	Grenade(sf::Vector2f origin, sf::Vector2f targetProjectile, PROJECTILE_OF projectileOf);
	void MoveProjectile(float _deltaTime);
	void SetExplosionSettings();
};


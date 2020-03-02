#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
class Weapon
{
public:
	sf::Mouse targetProjectile;
	sf::Vector2f origin;
	int weaponDamage;
	float speedBullet;
	float fireRate;

private:
	float _fireRate;

public:
	Weapon(int weaponDamage, float speedBullet, float fireRate);
	Projectile* CreateProjectile(sf::Vector2f targetProjectile);
	void UpdateOrigineProjectile(sf::Vector2f origin);
	void UpdateFireRate(float deltaTime);
};
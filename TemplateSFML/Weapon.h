#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <list>
class Weapon
{
public:
	sf::Mouse targetProjectile;
	sf::Vector2f origin;
	int weaponDamage;
	float speedBullet;
	float fireRate;

protected:
	float _fireRate;

public:
	Weapon(int weaponDamage, float speedBullet, float fireRate);
	virtual void Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile);
	virtual Projectile* CreateProjectile(sf::Vector2f targetProjectile);
	void UpdateOrigineProjectile(sf::Vector2f origin);
	void UpdateFireRate(float deltaTime);
};
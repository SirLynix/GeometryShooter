#pragma once
#include "Weapon.h"

class ShotGun : public Weapon
{

public:
	ShotGun();
	void Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJECTILE_OF projectileOf);
	Projectile* CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJECTILE_OF projectileOf);
};


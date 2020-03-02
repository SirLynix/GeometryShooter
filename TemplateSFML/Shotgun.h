#pragma once
#include "Weapon.h"

class ShotGun : public Weapon
{
public : 
	ShotGun();
	void Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJETILE_OF projectileOf);
	Projectile* CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJETILE_OF projectileOf);
	
};


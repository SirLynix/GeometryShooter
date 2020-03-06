#pragma once
#include "Weapon.h"

class ShotGun : public Weapon
{
public:
	ShotGun();
<<<<<<< HEAD
	void Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJECTILE_OF projectileOf);
	Projectile* CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJECTILE_OF projectileOf);
	
=======
	void Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJETILE_OF projectileOf);
	Projectile* CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJETILE_OF projectileOf);

>>>>>>> a7a65712bdf5f33f8459aefccb2a385cd9ccd558
};


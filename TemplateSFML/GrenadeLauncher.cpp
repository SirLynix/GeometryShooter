#include "GrenadeLauncher.h"
#include "Grenade.h"

GrenadeLauncher::GrenadeLauncher() : Weapon(3, 1.5f, 2.0f) 
{
	
}

void GrenadeLauncher::Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJECTILE_OF projectileOf)
{
	if (fireRate < 0) {
		return;
	}
	if (_fireRate < 0) {
		listProjectile->push_back(CreateProjectile(targetProjectile, 0.0f, projectileOf));
		_fireRate = fireRate;
	}
}

Projectile* GrenadeLauncher::CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJECTILE_OF projectileOf)
{
	double angle = atan2(targetProjectile.y - origin.y, targetProjectile.x - origin.x);
	

	return new Grenade(this->origin, targetProjectile, projectileOf);
}


#include "GrenadeLauncher.h"
#include "Grenade.h"

GrenadeLauncher::GrenadeLauncher() : Weapon(3, 1.5f, 1.7f, 6, "GrenadeLauncher", 0.1f, 3.0f)
{
	this->widthWeapon = 15;
	this->heightWeapon = 25;

	this->rectangle.setSize(sf::Vector2f(widthWeapon, heightWeapon));
	this->rectangle.setOrigin(sf::Vector2f(widthWeapon / 2, heightWeapon / 2));
	this->rectangle.setPosition(sf::Vector2f(this->origin.x, this->origin.y));
	this->rectangle.setFillColor(sf::Color(255, 255, 255)); //(228, 0, 250)
}

void GrenadeLauncher::Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJECTILE_OF projectileOf)
{
	if (fireRate < 0) {
		return;
	}
	if (cooldownFirerate < 0) {
		listProjectile->push_back(CreateProjectile(targetProjectile, 0.0f, projectileOf));
		cooldownFirerate = fireRate;
		ammo--;
	}
}

Projectile* GrenadeLauncher::CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJECTILE_OF projectileOf)
{
	double angle = atan2(targetProjectile.y - origin.y, targetProjectile.x - origin.x);


	return new Grenade(this->origin, targetProjectile, projectileOf, this->rectangle.getFillColor());
}


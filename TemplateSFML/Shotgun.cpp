#include "Shotgun.h"


ShotGun::ShotGun() : Weapon(1, 1.0f, .8f, 12, "Shotgun") {
	this->widthWeapon = 15;
	this->heightWeapon = 35;

	this->rectangle.setSize(sf::Vector2f(widthWeapon, heightWeapon));
	this->rectangle.setOrigin(sf::Vector2f(widthWeapon / 2, heightWeapon / 2));
	this->rectangle.setPosition(sf::Vector2f(this->origin.x, this->origin.y));
	this->rectangle.setFillColor(sf::Color::Red);
}

void ShotGun::Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJECTILE_OF projectileOf)
{
	if (_fireRate < 0) {
		listProjectile->push_back(new Projectile(this->weaponDamage, this->speedBullet, this->origin, targetProjectile, projectileOf));

		listProjectile->push_back(CreateProjectile(targetProjectile, 0.05f, projectileOf));
		listProjectile->push_back(CreateProjectile(targetProjectile, 0.1f, projectileOf));
		listProjectile->push_back(CreateProjectile(targetProjectile, -0.05f, projectileOf));
		listProjectile->push_back(CreateProjectile(targetProjectile, -0.1f, projectileOf));
		_fireRate = fireRate;
		ammo--;
	}

}

Projectile* ShotGun::CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJECTILE_OF projectileOf)

{
	int max = 5 + (this->speedBullet * 100);
	int min = -5 + (this->speedBullet * 100);
	if (min < 9)
	{
		min = 9;
	}
	float randomSpeed = (min + rand() % (max - min));
	double angle = atan2(targetProjectile.y - origin.y, targetProjectile.x - origin.x) + angleOffset;

	sf::Vector2f newTargetProjectile = sf::Vector2f(cos(angle) + this->origin.x, sin(angle) + this->origin.y);
	return new Projectile(this->weaponDamage, randomSpeed / 100, this->origin, newTargetProjectile, projectileOf);
}

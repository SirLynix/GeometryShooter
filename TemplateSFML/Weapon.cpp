#include "Weapon.h"
#include "Player.h"
#include "Projectile.h"
Weapon::Weapon(int weaponDamage, float speedBullet, float fireRate) : origin(sf::Vector2f(0, 0)), weaponDamage(weaponDamage), speedBullet(speedBullet), fireRate(fireRate), _fireRate(fireRate) {}

void Weapon::Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile)
{
	if (_fireRate < 0) {
		listProjectile->push_back(CreateProjectile(targetProjectile, 0.0f));
		_fireRate = fireRate;
	}

}

Projectile* Weapon::CreateProjectile(sf::Vector2f targetProjectile, float angleOffset)
{
	double angle = atan2(targetProjectile.y - origin.y, targetProjectile.x - origin.x);

	sf::Vector2f newTargetProjectile = sf::Vector2f(cos(angle) + this->origin.x, sin(angle) + this->origin.y);
	return new Projectile(this->weaponDamage, this->speedBullet, this->origin, newTargetProjectile);
}

void Weapon::UpdateOrigineProjectile(sf::Vector2f origin)
{
	this->origin = origin;
}

void Weapon::UpdateFireRate(float deltaTime) {
	this->_fireRate -= deltaTime;
}
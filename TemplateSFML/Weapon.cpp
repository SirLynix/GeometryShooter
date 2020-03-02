#include "Weapon.h"
#include "Player.h"
#include "Projectile.h"
Weapon::Weapon(int weaponDamage, float speedBullet, float fireRate) : origin(sf::Vector2f(0, 0)), weaponDamage(weaponDamage), speedBullet(speedBullet), fireRate(fireRate), _fireRate(fireRate) {}

void Weapon::Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile)
{
	if (_fireRate < 0) {
		listProjectile->push_back(CreateProjectile(targetProjectile));
		_fireRate = fireRate;
	}

}

Projectile* Weapon::CreateProjectile(sf::Vector2f targetProjectile)
{
	if (_fireRate > 0) {
		return nullptr;
	}
	_fireRate = fireRate;
	return new Projectile(this->weaponDamage, this->speedBullet, this->origin, targetProjectile);
}

void Weapon::UpdateOrigineProjectile(sf::Vector2f origin)
{
	this->origin = origin;
}

void Weapon::UpdateFireRate(float deltaTime) {
	this->_fireRate -= deltaTime;
}
#include "Weapon.h"
#include "Player.h"
#include "Projectile.h"

Weapon::Weapon(int weaponDamage, float speedBullet, float fireRate) : origin(sf::Vector2f(0, 0)), weaponDamage(weaponDamage), speedBullet(speedBullet), fireRate(fireRate), _fireRate(fireRate) {
	this->widthWeapon = 0;
	this->heightWeapon = 0;
}

void Weapon::Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJETILE_OF projectileOf)
{
	if (fireRate < 0) {
		return;
	}
	if (_fireRate < 0) {
		listProjectile->push_back(CreateProjectile(targetProjectile, 0.0f, projectileOf));
		_fireRate = fireRate;
	}

}

Projectile* Weapon::CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJETILE_OF projectileOf)
{
	double angle = atan2(targetProjectile.y - origin.y, targetProjectile.x - origin.x);

	return new Projectile(this->weaponDamage, this->speedBullet, this->origin, targetProjectile, projectileOf);
}

void Weapon::UpdateOrigineProjectile(sf::Vector2f origin)
{
	this->origin = origin;
	this->rectangle.setPosition(sf::Vector2f(this->origin.x, this->origin.y));
}

void Weapon::UpdateFireRate(float deltaTime) {
	this->_fireRate -= deltaTime;
}

void Weapon::DrawWeapon(sf::RenderWindow* window)
{
	window->draw(this->rectangle);
}

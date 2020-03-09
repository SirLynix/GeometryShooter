#include "Weapon.h"
#include "Player.h"
#include "Projectile.h"
<<<<<<< HEAD
Weapon::Weapon(int weaponDamage, float speedBullet, float fireRate, sf::String name) : origin(sf::Vector2f(0, 0)), weaponDamage(weaponDamage), speedBullet(speedBullet), fireRate(fireRate), _fireRate(fireRate) {
	
	this->heightWeapon = 0;
	this->widthWeapon = 0;
	this->name.setString(name);
=======
Weapon::Weapon(int weaponDamage, float speedBullet, float fireRate) : origin(sf::Vector2f(0, 0)), weaponDamage(weaponDamage), speedBullet(speedBullet), fireRate(fireRate), _fireRate(fireRate) {
	this->heightWeapon = 0;
	this->widthWeapon = 0;
>>>>>>> 0b3bf0db45cbba59c5c595f6d48995dfc83cba03
}

void Weapon::Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJECTILE_OF projectileOf)
{
	if (fireRate < 0) {
		return;
	}
	if (_fireRate < 0) {
		listProjectile->push_back(CreateProjectile(targetProjectile, 0.0f, projectileOf));
		_fireRate = fireRate;
	}

}

Projectile* Weapon::CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJECTILE_OF projectileOf)
{
	double angle = atan2(targetProjectile.y - origin.y, targetProjectile.x - origin.x);
	
	if (projectileOf == PROJECTILE_OF::ENEMY)
	{
		Projectile* projectile = new Projectile(this->weaponDamage, this->speedBullet, this->origin, targetProjectile, projectileOf);
		projectile->projectile.setFillColor(sf::Color::Cyan);
		return projectile;
	}
	else
	{
		Projectile* projectile = new Projectile(this->weaponDamage, this->speedBullet, this->origin, targetProjectile, projectileOf);
		return projectile;
	}	

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

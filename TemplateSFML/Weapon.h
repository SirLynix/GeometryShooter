#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <list>
class Weapon
{
public:
	sf::RectangleShape rectangle;
	sf::Mouse targetProjectile;
	sf::Vector2f origin;
	int weaponDamage;
	float speedBullet;
	float fireRate;
	float widthWeapon;
	float heightWeapon;
	float ammo;

protected:
	float _fireRate;

public:
	Weapon(int weaponDamage, float speedBullet, float cooldown, float ammo);
	virtual void Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJECTILE_OF projectileOf);
	virtual Projectile* CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJECTILE_OF projectileOf);
	void UpdateOrigineProjectile(sf::Vector2f origin);
	void UpdateFireRate(float deltaTime);
	void DrawWeapon(sf::RenderWindow* window);
};
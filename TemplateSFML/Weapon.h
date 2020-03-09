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
<<<<<<< HEAD
	float ammo;
=======
	sf::Text name;
>>>>>>> 34bbd960e3a27360bd77ee6bc29e1f34a5244e87

protected:
	float _fireRate;

public:
<<<<<<< HEAD
	Weapon(int weaponDamage, float speedBullet, float cooldown, float ammo);
=======
	Weapon(int weaponDamage, float speedBullet, float fireRate, sf::String name);
>>>>>>> 34bbd960e3a27360bd77ee6bc29e1f34a5244e87
	virtual void Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJECTILE_OF projectileOf);
	virtual Projectile* CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJECTILE_OF projectileOf);
	void UpdateOrigineProjectile(sf::Vector2f origin);
	void UpdateFireRate(float deltaTime);
	void DrawWeapon(sf::RenderWindow* window);
};
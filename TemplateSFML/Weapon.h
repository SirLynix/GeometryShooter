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
	int ammo;
	sf::Text name;
	float couldownFireRate;
	float amplitudeShakeScreen;
	float timeShake;

public:
	Weapon(int weaponDamage, float speedBullet, float fireRate, int ammo, sf::String name, float timeShake, float amplitudeShakeScreen);
	virtual void Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJECTILE_OF projectileOf);
	virtual Projectile* CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJECTILE_OF projectileOf);
	void UpdateOrigineProjectile(sf::Vector2f origin);
	void UpdateFireRate(float deltaTime);
	void DrawWeapon(sf::RenderWindow* window);
};
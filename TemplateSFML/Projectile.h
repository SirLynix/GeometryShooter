#pragma once
#include <SFML/Graphics.hpp>

enum class PROJECTILE_OF
{
	PLAYER, ENEMY
};

enum class TYPE_PROJECTILE
{
	GRENADE, BULLET
};

class Projectile
{
public:
	int weaponDamage;
	float speed;
	sf::CircleShape projectile;
	sf::Vector2f origin;
	sf::Vector2f targetProjectile;
	PROJECTILE_OF projectileOf;
	TYPE_PROJECTILE typeProjectile;
	bool canExplode;
	bool toDestruct = false;
	float explosionCooldown = -1.0f;
	float projectileCooldown = 0.25f;
	bool colorChange = false;
	sf::Color colorProjectil;
	
public:
	Projectile(int weaponDamage, float speed, sf::Vector2f origin, sf::Vector2f targetProjectile, PROJECTILE_OF projectileOf, sf::Color colorProjectil);
	virtual void MoveProjectile(float _deltaTime);
	void DisplayProjectile(sf::RenderWindow* window);
	void UpdateRadius(float _deltaTime);
	void UpdateExplosionCooldown(float _deltaTime);
	virtual void SetExplosionSettings();
	void ChangeColor();
	
};
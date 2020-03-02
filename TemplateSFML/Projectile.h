#pragma once
#include <SFML/Graphics.hpp>

enum class PROJETILE_OF
{
	PLAYER, ENEMY
};

class Projectile
{
public:
	int weaponDamage;
	float speed;
	sf::CircleShape projectile;
	sf::Vector2f origin;
	sf::Vector2f targetProjectile;
	PROJETILE_OF projectileOf;
public:
	Projectile(int weaponDamage, float speed, sf::Vector2f origin, sf::Vector2f targetProjectile, PROJETILE_OF projectileOf);
	void MoveProjectile(float _deltaTime);
	void DisplayProjectile(sf::RenderWindow* window);
};
#pragma once
#include <SFML/Graphics.hpp>

class Projectile
{
public:
	int weaponDamage;
	float speed;
	sf::CircleShape projectile;
	sf::Vector2f origin;
	sf::Vector2f targetProjectile;

public:
	Projectile(int weaponDamage, float speed, sf::Vector2f origin, sf::Vector2f targetProjectile);
	void MoveProjectile(float _deltaTime);
	void DisplayProjectile(sf::RenderWindow* window);
};
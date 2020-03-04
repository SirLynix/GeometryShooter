#include "Projectile.h"

Projectile::Projectile(int weaponDamage, float speed, sf::Vector2f origin, sf::Vector2f targetProjectile, PROJETILE_OF projectilOf) : weaponDamage(weaponDamage), speed(speed), origin(origin), targetProjectile(targetProjectile), projectileOf(projectilOf)
{
	this->projectile.setRadius(5);
	this->projectile.setFillColor(sf::Color(255, 255, 255));
	this->projectile.setPosition(origin);
}

void Projectile::MoveProjectile(float _deltaTime)
{
	float serializableSpeed = this->speed * _deltaTime * 1000;

	double angle = atan2(targetProjectile.y - origin.y, targetProjectile.x - origin.x);

	float moveX = serializableSpeed * cos(angle);
	float moveY = serializableSpeed * sin(angle);

	this->projectile.setPosition(this->projectile.getPosition().x + moveX, this->projectile.getPosition().y + moveY);

}

void Projectile::DisplayProjectile(sf::RenderWindow* window)
{
	window->draw(this->projectile);
}
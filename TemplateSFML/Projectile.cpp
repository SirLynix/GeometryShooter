#include "Projectile.h"

Projectile::Projectile(int weaponDamage, float speed, sf::Vector2f origin, sf::Vector2f targetProjectile, PROJECTILE_OF projectileOf) : weaponDamage(weaponDamage), speed(speed), origin(origin), targetProjectile(targetProjectile), projectileOf(projectileOf)
{
	this->projectile.setRadius(5);
	this->projectile.setFillColor(sf::Color::Green);
	this->projectile.setPosition(origin);
	this->projectile.setOrigin(5, 5);
	this->canExplode = false;
	this->explosionCooldown = -1.0f;
	this->typeProjectile = TYPE_PROJECTILE::BULLET;
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
void Projectile::UpdateRadius(float _deltaTime)
{
	if (this->projectile.getRadius() > 150.0f)
	{
		toDestruct = true;
		return;
	}
	this->projectile.setRadius(projectile.getRadius() + (600 * _deltaTime));
	this->projectile.setOrigin(this->projectile.getRadius(), this->projectile.getRadius());
}

void Projectile::UpdateExplosionCooldown(float _deltaTime)
{
	explosionCooldown -= _deltaTime;
	
	if (explosionCooldown <= 0.0f)
	{
		canExplode = true;
		SetExplosionSettings();
	}
}

void Projectile::SetExplosionSettings()
{

}

void Projectile::ChangeColor()
{
	if (projectileCooldown <= 0.0f)
	{
		colorChange = !colorChange;
		projectileCooldown = 0.25f;
	}

	if (colorChange)
	{
		this->projectile.setFillColor(sf::Color::Red);
	}
	else
	{
		this->projectile.setFillColor(sf::Color::Green);
	}
	
}

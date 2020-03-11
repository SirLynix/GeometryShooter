#include "Grenade.h"

Grenade::Grenade(sf::Vector2f origin, sf::Vector2f targetProjectile, PROJECTILE_OF projectileOf, sf::Color colorProjectil) : Projectile(3, 0.75f,origin,targetProjectile, projectileOf, colorProjectil)
{
	this->shockWave.setFillColor(colorProjectil);
	this->typeProjectile = TYPE_PROJECTILE::GRENADE;
	this->projectile.setRadius(10);
	this->projectile.setOrigin(10, 10);
}

void Grenade::MoveProjectile(float _deltaTime)
{

	projectileCooldown -= _deltaTime;

	if (!canExplode)
	{
		ChangeColor();

	}
	
	if (canExplode || explosionCooldown > -1.0f)
	{
		return;
	}



	if ((this->origin.x -2) < this->targetProjectile.x && this->targetProjectile.x < (this->origin.x + 2) &&
		(this->origin.y - 2) < this->targetProjectile.y && this->targetProjectile.y < (this->origin.y + 2))
	{
		explosionCooldown = 1.0f;
		return;
	}
	float serializableSpeed = this->speed * _deltaTime * 1000;

	double angle = atan2(targetProjectile.y - origin.y, targetProjectile.x - origin.x);

	float moveX = serializableSpeed * cos(angle);
	float moveY = serializableSpeed * sin(angle);

	this->projectile.setPosition(this->projectile.getPosition().x + moveX, this->projectile.getPosition().y + moveY);

	this->origin.x += moveX;
	this->origin.y += moveY;

	

}

void Grenade::SetExplosionSettings()
{
	this->projectile.setFillColor(sf::Color(0, 0, 0, 0));
	this->projectile.setOutlineColor(this->colorProjectil);
	this->projectile.setOutlineThickness(4.0f);

}



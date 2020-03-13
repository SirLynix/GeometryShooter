#include "Weapon.h"
#include "Player.h"
#include "Gun.h"
#include "Shotgun.h"
#include "MachineGun.h"
#include "GrenadeLauncher.h"
#include "Projectile.h"

Weapon::Weapon(int weaponDamage, float speedBullet, float fireRate, int maxAmmo, sf::String name, float timeShake, float amplitudeShakeScreen) : origin(sf::Vector2f(0, 0)), weaponDamage(weaponDamage), speedBullet(speedBullet), fireRate(fireRate), cooldownFirerate(0), ammo(maxAmmo), maxAmmo(maxAmmo), timeShake(timeShake), amplitudeShakeScreen(amplitudeShakeScreen) {

	this->heightWeapon = 0;
	this->widthWeapon = 0;
	this->name.setString(name);
}

void Weapon::Shoot(sf::Vector2f targetProjectile, std::list<Projectile*>* listProjectile, PROJECTILE_OF projectileOf)
{

	if (fireRate < 0) {
		return;
	}
	if (cooldownFirerate < 0) {
		listProjectile->push_back(CreateProjectile(targetProjectile, 0.0f, projectileOf));
		cooldownFirerate = fireRate;
		ammo--;
	}
}

Weapon* Weapon::Clone() {
	Weapon* clone = new Gun();
	string name = this->name.getString();
	if (name == sf::String("Shotgun")) {
		clone = new ShotGun();
	}
	if (name == sf::String("Machinegun")) {
		clone = new MachineGun();
	}
	if (name == sf::String("GrenadeLauncher")) {
		clone = new GrenadeLauncher();
	}
	return clone;
}

Projectile* Weapon::CreateProjectile(sf::Vector2f targetProjectile, float angleOffset, PROJECTILE_OF projectileOf)
{
	double angle = atan2(targetProjectile.y - origin.y, targetProjectile.x - origin.x);

	if (projectileOf == PROJECTILE_OF::ENEMY)
	{
		Projectile* projectile = new Projectile(this->weaponDamage, this->speedBullet, this->origin, targetProjectile, projectileOf, this->rectangle.getFillColor());
		projectile->projectile.setFillColor(sf::Color::Cyan);
		return projectile;
	} else
	{
		Projectile* projectile = new Projectile(this->weaponDamage, this->speedBullet, this->origin, targetProjectile, projectileOf, this->rectangle.getFillColor());
		return projectile;
	}

}

void Weapon::UpdateOrigineProjectile(sf::Vector2f origin)
{
	this->origin = origin;
	this->rectangle.setPosition(sf::Vector2f(this->origin.x, this->origin.y));
}

void Weapon::UpdateFireRate(float deltaTime) {
	this->cooldownFirerate -= deltaTime;
}

void Weapon::DrawWeapon(sf::RenderWindow* window)
{
	window->draw(this->rectangle);
}

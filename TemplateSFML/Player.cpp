#include <iostream>
#include "Player.h"
#include "Character.h"
#include "Arena.h"
#include "Enemy.h"

const int radiusPlayer = 20;
const float PI = 3.14159265359;

Player::Player(int _posX, int _posY, Weapon* weapon) : Character(3, 180.0f, _posX, _posY, false, weapon), hasBulletTime(false), canMove(true), isDashing(false), dashFactor(5.f) {
	this->baseSpeed = this->speed;

	this->cercle.setPosition(sf::Vector2f(this->posX, this->posY));
	this->cercle.setRadius(radiusPlayer);
	this->cercle.setOrigin(radiusPlayer, radiusPlayer);
	this->cercle.setFillColor(sf::Color::Green);

	this->typeMovement = ACTION::NONE;

	this->spawnCircle.setPosition(sf::Vector2f(this->posX, this->posY));
	this->spawnCircle.setRadius(radiusPlayer * 8);
	this->spawnCircle.setOrigin(sf::Vector2f(radiusPlayer * 8, radiusPlayer * 8));
}

void Player::Dash()
{
	if (!this->isDashing) {
		this->baseSpeed = this->speed;
		this->isDashing = true;
		this->speed *= this->dashFactor;
	}
}

void Player::SpeedDown() {
}

void Player::DrawPlayer(sf::RenderWindow* window)
{
	UpdateCerclePos();
	window->draw(this->cercle);
	this->weapon->DrawWeapon(window);
}

void Player::MoveTo(float _posX, float _posY)
{
	this->posX += _posX;
	this->posY += _posY;
}

void Player::SetTypeMovment(ACTION _newAction)
{
	this->typeMovement = _newAction;
}

bool Player::CheckForMovement(ACTION _action)
{
	if ((this->typeMovement == ACTION::RIGHT && _action == ACTION::LEFT) ||
		(this->typeMovement == ACTION::LEFT && _action == ACTION::RIGHT) ||
		(this->typeMovement == ACTION::UP && _action == ACTION::DOWN) ||
		(this->typeMovement == ACTION::DOWN && _action == ACTION::UP)) {
		return false;
	}

	return true;
}

void Player::SetComboMovement(ACTION _action)
{
	if ((_action == ACTION::LEFT && this->typeMovement == ACTION::UP) || (_action == ACTION::UP && this->typeMovement == ACTION::LEFT)) {
		this->SetTypeMovment(ACTION::UP_LEFT);
	}
	else if ((_action == ACTION::RIGHT && this->typeMovement == ACTION::UP) || (_action == ACTION::UP && this->typeMovement == ACTION::RIGHT)) {
		this->SetTypeMovment(ACTION::UP_RIGHT);
	}
	else if ((_action == ACTION::LEFT && this->typeMovement == ACTION::DOWN) || (_action == ACTION::DOWN && this->typeMovement == ACTION::LEFT)) {
		this->SetTypeMovment(ACTION::DOWN_LEFT);
	}
	else if ((_action == ACTION::RIGHT && this->typeMovement == ACTION::DOWN) || (_action == ACTION::DOWN && this->typeMovement == ACTION::RIGHT)) {
		this->SetTypeMovment(ACTION::DOWN_RIGHT);
	}
}

void Player::SetWeapon(Weapon* weapon)
{
	this->weapon = weapon;
}

void Player::UpdateCerclePos()
{
	this->spawnCircle.setPosition(sf::Vector2f(this->posX, this->posY));
	this->cercle.setPosition(sf::Vector2f(this->posX, this->posY));
}

void Player::PerformAction(Arena* arene, std::list<Enemy*> listEnemy, float _deltaTime)
{

	if (!this->canMove || this->typeMovement == ACTION::NONE) {
		return;
	}

	float x = 0.0f;
	float y = 0.0f;

	if (this->typeMovement == ACTION::UP) {
		y = -this->speed;
	}
	else if (this->typeMovement == ACTION::DOWN) {
		y = this->speed;
	}
	else if (this->typeMovement == ACTION::LEFT) {
		x = -this->speed;
	}
	else if (this->typeMovement == ACTION::RIGHT) {
		x = this->speed, 0;
	}
	else if (this->typeMovement == ACTION::UP_LEFT) {
		x = -this->speed;
		y = -this->speed;
	}
	else if (this->typeMovement == ACTION::UP_RIGHT) {
		x = this->speed;
		y = -this->speed;
	}
	else if (this->typeMovement == ACTION::DOWN_LEFT) {
		x = -this->speed;
		y = this->speed;
	}
	else if (this->typeMovement == ACTION::DOWN_RIGHT) {
		x = this->speed;
		y = this->speed;
	}
	else if (this->typeMovement == ACTION::RIGHT) {
		x = this->speed;
	}
	else if (this->typeMovement == ACTION::UP_LEFT) {
		x = -this->speed / sqrt(2);
		y = -this->speed / sqrt(2);
	}
	else if (this->typeMovement == ACTION::UP_RIGHT) {
		x = this->speed / sqrt(2);
		y = -this->speed / sqrt(2);
	}
	else if (this->typeMovement == ACTION::DOWN_LEFT) {
		x = -this->speed / sqrt(2);
		y = this->speed / sqrt(2);
	}
	else if (this->typeMovement == ACTION::DOWN_RIGHT) {
		x = this->speed / sqrt(2);
		y = this->speed / sqrt(2);
	}

	x *= _deltaTime;
	y *= _deltaTime;
	bool canMove = true;

	this->cercle.setPosition(sf::Vector2f(this->posX + x, this->posY + y));

	std::list<Brique*>::iterator it = arene->briques.begin();
	while (it != arene->briques.end()) {
		if ((*it)->rectangle.getGlobalBounds().intersects(this->cercle.getGlobalBounds())) {
			canMove = false;
		}
		it++;
	}

	std::list<Enemy*>::iterator it2 = listEnemy.begin();
	while (it2 != listEnemy.end()) {
		if ((*it2)->rectangle.getGlobalBounds().intersects(this->cercle.getGlobalBounds())) {
			canMove = false;
		}
		it2++;
	}

	this->cercle.setPosition(sf::Vector2f(this->posX, this->posY));

	if (canMove) {
		this->MoveTo(x, y);
	}
}

void Player::RotationPlayer(float angleRotation) {

	this->weapon->rectangle.setRotation(angleRotation * (180 / PI) + 90);

	float angleWeapon = 90 * (PI / 180);
	float distanceWeaponFactor = 1.0f;
	float posXOrigineFire = (this->posX + cos(angleRotation + angleWeapon) * this->cercle.getRadius() * distanceWeaponFactor);
	float posYOrigineFire = (this->posY + sin(angleRotation + angleWeapon) * this->cercle.getRadius() * distanceWeaponFactor);

	this->weapon->UpdateOrigineProjectile(sf::Vector2f(posXOrigineFire, posYOrigineFire));
}
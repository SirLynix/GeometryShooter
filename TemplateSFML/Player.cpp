#include <iostream>
#include "Player.h"
#include "Character.h"
#include "Arena.h"
#include "Enemy.h"

const int radiusPlayer = 20;
const float PI = 3.14159265359;

Player::Player(int _posX, int _posY, Weapon* weapon) : Character(3, 220.0f, _posX, _posY, false, weapon), hasBulletTime(false), canMove(true), isDashing(false), dashFactor(5.f), dashDuration(.2f) {

	this->baseSpeed = this->speed;
	this->cercle.setPosition(sf::Vector2f(this->posX, this->posY));
	this->cercle.setRadius(radiusPlayer);
	this->cercle.setOrigin(radiusPlayer, radiusPlayer);
	this->cercle.setFillColor(sf::Color::Green);

	this->isAkimbo = false;
	this->akimboCD = 0.f;
	this->akimboLeft = false;

	this->canDash = true;
	this->baseCD = 1.5f;

	this->typeMovement = ACTION::NONE;

	this->spawnCircle.setPosition(sf::Vector2f(this->posX, this->posY));
	this->spawnCircle.setRadius(radiusPlayer * 12);
	this->spawnCircle.setOrigin(sf::Vector2f(radiusPlayer * 12, radiusPlayer * 12));
}

void Player::Dash()
{
	if (this->canDash) {
		this->isDashing = true;
		this->canDash = false;
		this->baseSpeed = this->speed;

		this->speed *= this->dashFactor;
		buffer.loadFromFile("Dash.wav");
		sound.setVolume(100.0f);
		sound.setBuffer(buffer);
		sound.play();
		canPlay = false;
	}
}

void Player::DrawPlayer(sf::RenderWindow* window)
{
	UpdateCerclePos();
	window->draw(this->cercle);

	this->weapon->DrawWeapon(window);
	if (this->isAkimbo) {
		this->akimbo->DrawWeapon(window);
	}
}

void Player::MoveTo(float _posX, float _posY)
{
	this->posX += _posX;
	this->posY += _posY;
}

void Player::addAction(ACTION actionToAdd)
{
	this->listAction.push_back(actionToAdd);
}

void Player::removeAction(ACTION actionToDel)
{
	std::list<ACTION>::iterator it = this->listAction.begin();
	while (it != this->listAction.end()) {
		if ((*it) == actionToDel) {
			it = this->listAction.erase(it);
		} else {
			it++;
		}
	}
}

void Player::UpdateAkimbo(float deltaTime) {
	if (this->isAkimbo && this->akimboCD > 0.f) {
		this->akimboCD -= deltaTime;
	} else {
		this->isAkimbo = false;
	}
}

void Player::UpdateDirectionMovement()
{

	if (this->typeMovement == ACTION::DEAD) {
		return;
	}

	bool isUp = false;
	bool isDown = false;
	bool isLeft = false;
	bool isRight = false;

	std::list<ACTION>::iterator it = this->listAction.begin();
	while (it != this->listAction.end()) {
		if ((*it) == ACTION::UP) {
			isUp = true;
		} else if ((*it) == ACTION::DOWN) {
			isDown = true;
		} else if ((*it) == ACTION::LEFT) {
			isLeft = true;
		} else if ((*it) == ACTION::RIGHT) {
			isRight = true;
		}
		it++;
	}

	if (isUp && isDown && isLeft && isRight) {
		this->SetTypeMovment(ACTION::NONE);
	} else if (isUp && isDown && isLeft) {
		this->SetTypeMovment(ACTION::LEFT);
	} else if (isUp && isDown && isRight) {
		this->SetTypeMovment(ACTION::RIGHT);
	} else if (isLeft && isRight && isUp) {
		this->SetTypeMovment(ACTION::UP);
	} else if (isLeft && isRight && isDown) {
		this->SetTypeMovment(ACTION::DOWN);
	} else if ((isLeft && isRight) || (isUp && isDown)) {
		this->SetTypeMovment(ACTION::NONE);
	} else if (isLeft && isUp) {
		this->SetTypeMovment(ACTION::UP_LEFT);
	} else if (isLeft && isDown) {
		this->SetTypeMovment(ACTION::DOWN_LEFT);
	} else if (isRight && isUp) {
		this->SetTypeMovment(ACTION::UP_RIGHT);
	} else if (isRight && isDown) {
		this->SetTypeMovment(ACTION::DOWN_RIGHT);
	} else if (isDown) {
		this->SetTypeMovment(ACTION::DOWN);
	} else if (isUp) {
		this->SetTypeMovment(ACTION::UP);
	} else if (isLeft) {
		this->SetTypeMovment(ACTION::LEFT);
	} else if (isRight) {
		this->SetTypeMovment(ACTION::RIGHT);
	} else {
		this->SetTypeMovment(ACTION::NONE);
	}


}

void Player::SetTypeMovment(ACTION _newAction)
{
	this->typeMovement = _newAction;
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
	UpdateDirectionMovement();
	if (!this->canMove || this->typeMovement == ACTION::NONE) {
		return;
	}

	float x = 0.0f;
	float y = 0.0f;

	if (this->typeMovement == ACTION::UP) {
		y = -this->speed;
	} else if (this->typeMovement == ACTION::DOWN) {
		y = this->speed;
	} else if (this->typeMovement == ACTION::LEFT) {
		x = -this->speed;
	} else if (this->typeMovement == ACTION::RIGHT) {
		x = this->speed;
	} else if (this->typeMovement == ACTION::UP_LEFT) {
		x = -this->speed / sqrt(2);
		y = -this->speed / sqrt(2);
	} else if (this->typeMovement == ACTION::UP_RIGHT) {
		x = this->speed / sqrt(2);
		y = -this->speed / sqrt(2);
	} else if (this->typeMovement == ACTION::DOWN_LEFT) {
		x = -this->speed / sqrt(2);
		y = this->speed / sqrt(2);
	} else if (this->typeMovement == ACTION::DOWN_RIGHT) {
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
	sf::Vector2f origin = this->CalculOrigineProj(angleRotation, angleWeapon);
	this->weapon->UpdateOrigineProjectile(origin);

	if (this->isAkimbo) {
		this->akimbo->rectangle.setRotation(angleRotation * (180 / PI) + 90);

		float angleAkimbo = -90 * (PI / 180);
		sf::Vector2f origin = this->CalculOrigineProj(angleRotation, angleAkimbo);
		this->akimbo->UpdateOrigineProjectile(origin);
	}
}

sf::Vector2f Player::CalculOrigineProj(float angleRotation, float angleWeapon) {
	float distanceWeaponFactor = 1.0f;
	float posXOrigineFire = (this->posX + cos(angleRotation + angleWeapon) * this->cercle.getRadius() * distanceWeaponFactor);
	float posYOrigineFire = (this->posY + sin(angleRotation + angleWeapon) * this->cercle.getRadius() * distanceWeaponFactor);
	return sf::Vector2f(posXOrigineFire, posYOrigineFire);
}

void Player::FeedbackDamageTaken(float _deltaTime)
{
	if (this->hasTakenDamage == true)
	{
		if (colorChangeDamage >= 0.0f)
		{
			isInvincible = true;
			this->cercle.setFillColor(sf::Color::Red);
			colorChangeDamage -= _deltaTime;
		} else
		{
			this->cercle.setFillColor(sf::Color::Green);
			colorChangeDamage = 0.1f;
			hasTakenDamage = false;
			isInvincible = false;;
		}

	}
}

#include "Enemy.h"

Enemy::Enemy(float _posX, float _posY, int thicknessesEnemy, Weapon* weapon) : Character(3, 2.5f, _posX, _posY, true, weapon)
{
	this->UpdateEnemyPos();
	this->rectangle.setSize(sf::Vector2f(thicknessesEnemy, thicknessesEnemy));
	this->rectangle.setOrigin(thicknessesEnemy / 2, thicknessesEnemy / 2);
	this->target = sf::Vector2f(0, 0);

	this->pv1.setSize(sf::Vector2f(thicknessesEnemy / 4, 5));
	this->pv1.setOrigin(this->pv1.getSize().x / 2, this->pv1.getSize().y / 2);
	this->pv1.setFillColor(sf::Color::Green);

	this->pv2.setSize(sf::Vector2f(thicknessesEnemy / 4, 5));
	this->pv2.setOrigin(this->pv2.getSize().x / 2, this->pv2.getSize().y / 2);
	this->pv2.setFillColor(sf::Color::Green);

	this->pv3.setSize(sf::Vector2f(thicknessesEnemy / 4, 5));
	this->pv3.setOrigin(this->pv3.getSize().x / 2, this->pv3.getSize().y / 2);
	this->pv3.setFillColor(sf::Color::Green);
}

void Enemy::UpdateEnemyPos()
{
	this->rectangle.setPosition(this->posX, this->posY);
	this->UpdatePositionUiPv();
}


void Enemy::UpdatePositionUiPv()
{
	this->pv1.setPosition(this->posX - this->pv1.getSize().x - OffsetPosXOfPV, this->posY - this->rectangle.getSize().y + OffsetPosYOfPV);

	this->pv2.setPosition(this->posX, this->posY - this->rectangle.getSize().y + OffsetPosYOfPV);

	this->pv3.setPosition(this->posX + this->pv3.getSize().x + OffsetPosXOfPV, this->posY - this->rectangle.getSize().y + OffsetPosYOfPV);
}

void Enemy::DisplayEnemy(sf::RenderWindow* window)
{
	this->UpdateEnemyPos();
	window->draw(this->rectangle);
	window->draw(this->pv1);
	window->draw(this->pv2);
	window->draw(this->pv3);
}

void Enemy::UpdateTarget(sf::Vector2f newTarget)
{
	this->target = newTarget;
}

void Enemy::UpdatePos(float x, float y)
{
	this->rectangle.setPosition(this->rectangle.getPosition().x + x, this->rectangle.getPosition().y + y);
}

void Enemy::UpdateUiToPv()
{
	if (this->vie == 1) {
		this->pv1.setFillColor(sf::Color::Red);

		this->pv2.setFillColor(sf::Color::Transparent);

		this->pv3.setFillColor(sf::Color::Transparent);
	}
	else if (this->vie == 2) {
		this->pv1.setFillColor(sf::Color(255, 140, 0));

		this->pv2.setFillColor(sf::Color(255, 140, 0));

		this->pv3.setFillColor(sf::Color::Transparent);
	}
	else if (this->vie >= 3) {
		this->pv1.setFillColor(sf::Color::Green);

		this->pv2.setFillColor(sf::Color::Green);

		this->pv3.setFillColor(sf::Color::Green);
	}
	else {
		this->pv1.setFillColor(sf::Color::Transparent);

		this->pv2.setFillColor(sf::Color::Transparent);

		this->pv3.setFillColor(sf::Color::Transparent);
	}
}

void Enemy::PerformAction(float _deltaTime) {}

float Enemy::GetNextMovementX()
{
	return 0.0f;
}

float Enemy::GetNextMovementY()
{
	return 0.0f;
}

bool Enemy::IsOnColliderWithEnemy(std::list<Enemy*> listEnemy)
{
	bool isCollider = false;
	std::list<Enemy*>::iterator it = listEnemy.begin();
	while (it != listEnemy.end()) {
		if ((*it) != this && this->rectangle.getGlobalBounds().intersects((*it)->rectangle.getGlobalBounds())) {
			isCollider = true;
		}
		it++;
	}
	return isCollider;
}

bool Enemy::IsOnColliderWithBrique(std::list<Brique*> listBrique)
{
	std::list<Brique*>::iterator it = listBrique.begin();
	while (it != listBrique.end()) {
		if (this->rectangle.getGlobalBounds().intersects((*it)->rectangle.getGlobalBounds())) {
			return true;
		}
		it++;
	}
	return false;
}
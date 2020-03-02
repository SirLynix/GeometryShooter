#include "Enemy.h"

Enemy::Enemy(float _posX, float _posY, int thicknessesEnemy, Weapon* weapon) : Character(100, 0.025f, _posX, _posY, true, weapon)
{
	this->UpdateEnemyPos();
	this->rectangle.setSize(sf::Vector2f(thicknessesEnemy, thicknessesEnemy));
	this->rectangle.setOrigin(thicknessesEnemy / 2, thicknessesEnemy / 2);
	this->target = sf::Vector2f(0, 0);
}

void Enemy::UpdateEnemyPos()
{
	this->rectangle.setPosition(this->posX, this->posY);
}

void Enemy::DisplayEnemy(sf::RenderWindow* window)
{
	this->UpdateEnemyPos();
	window->draw(this->rectangle);
}

void Enemy::UpdateTarget(sf::Vector2f newTarget)
{
	this->target = newTarget;
}

void Enemy::UpdatePos(float x, float y)
{
	this->rectangle.setPosition(this->rectangle.getPosition().x + x, this->rectangle.getPosition().y + y);
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
		if ((*it) == this != this->rectangle.getGlobalBounds().intersects((*it)->rectangle.getGlobalBounds())) {
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
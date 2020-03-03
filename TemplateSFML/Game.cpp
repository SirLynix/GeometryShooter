#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Game.h"
#include "Enemy.h"
#include "Zombie.h"
#include "Archer.h"
#include "Weapon.h"
#include "Projectile.h"
#include "Gun.h"

float Clamp(float f, float limitMax, float limitMin);
float Abs(float f);

const int thicknessesBrique = 10;
const int thicknessesEnemy = 50;

Game::Game(Player* _player, int height, int width, sf::RenderWindow* _window) : player(_player), window(_window)
{
	srand(time(NULL));
	int nbTiles = 100;
	sf::RectangleShape*** echiquier = new sf::RectangleShape * *[nbTiles];
	for (size_t i = 0; i < nbTiles; i++)
	{
		echiquier[i] = new sf::RectangleShape * [nbTiles];

		for (size_t j = 0; j < nbTiles; j++)
		{
			echiquier[i][j] = new sf::RectangleShape{};
			sf::Color color = (i + j) % 2 == 0 ? sf::Color(0, 0, 0) : sf::Color(40, 40, 40);
			echiquier[i][j]->setFillColor(color);
			echiquier[i][j]->setSize(sf::Vector2f(50, 50));
			echiquier[i][j]->setPosition(sf::Vector2f(i * 50, j * 50));
		}
	}

	this->arena = new Arena(height, width, thicknessesBrique, echiquier, nbTiles, 50);
	this->arena->CreateArena();
	this->deltaTime = 0;
	this->totalTime = 0;
}

void Game::AddEnemy(Enemy* enemyToAdd)
{
	listEnemy.push_back(enemyToAdd);
}

void Game::RemoveEnemy(Enemy* enemyToRemove)
{
	listEnemy.remove(enemyToRemove);
}

void Game::DisplayGame()
{
	this->arena->DisplayArena(this->window);
	this->player->DrawPlayer(this->window);
	std::list<Enemy*>::iterator it = this->listEnemy.begin();
	while (it != this->listEnemy.end()) {
		(*it)->DisplayEnemy(this->window);
		it++;
	}

	std::list<Projectile*>::iterator it2 = this->listProjectile.begin();
	while (it2 != this->listProjectile.end()) {
		(*it2)->DisplayProjectile(this->window);
		it2++;
	}
}

void Game::CreateWave(int nbZombie, int nbArcher)
{
	int borneMaxX = this->window->getSize().x - thicknessesEnemy / 2 - thicknessesBrique;
	int borneMaxY = this->window->getSize().y - thicknessesEnemy / 2 - thicknessesBrique;

	int borneMin = thicknessesEnemy / 2 + thicknessesBrique;

	int x;
	int y;
	bool enemiSpawn = false;
	int nbEssaieSpawn = 0;
	for (int i = 0; i < nbZombie; i++)
	{
		enemiSpawn = false;
		nbEssaieSpawn = 0;

		while ( !enemiSpawn && nbEssaieSpawn < 5 ) {
			nbEssaieSpawn++;
			x = rand() % (borneMaxX + 1);
			y = rand() % (borneMaxY + 1);
			if (x < borneMin) {
				x = borneMin;
			}
			if (y < borneMin) {
				y = borneMin;
			}
			Enemy* enemyZombie = new Zombie(x, y, thicknessesEnemy, new Weapon(1, 2, -1));
			if (!this->player->spawnCircle.getGlobalBounds().intersects(enemyZombie->rectangle.getGlobalBounds()))
			{
				enemiSpawn = true;
				this->AddEnemy(enemyZombie);
			}
		}
	}

	for (int i = 0; i < nbArcher; i++)
	{
		enemiSpawn = false;
		nbEssaieSpawn = 0;
		while (!enemiSpawn && nbEssaieSpawn < 5) {
			nbEssaieSpawn++;
			x = rand() % (borneMaxX + 1);
			y = rand() % (borneMaxY + 1);
			if (x < borneMin) {
				x = borneMin;
			}
			if (y < borneMin) {
				y = borneMin;
			}
			Enemy* enemyArcher = new Archer(x, y, thicknessesEnemy, new Gun());
			if (!this->player->spawnCircle.getGlobalBounds().intersects(enemyArcher->rectangle.getGlobalBounds()))
			{
				enemiSpawn = true;
				this->AddEnemy(enemyArcher);
			}
		}
	}
}

void Game::UpdateTime(float _deltaTime)
{
	this->totalTime += _deltaTime;
	this->deltaTime = _deltaTime;
	this->player->PerformAction(this->arena, this->listEnemy, deltaTime);
	this->player->weapon->UpdateFireRate(deltaTime);

	std::list<Enemy*>::iterator it = this->listEnemy.begin();
	while (it != this->listEnemy.end()) {
		(*it)->weapon->UpdateFireRate(_deltaTime);
		it++;
	}

}

void Game::MoveAllEnemy()
{
	std::list<Enemy*>::iterator it = this->listEnemy.begin();
	while (it != this->listEnemy.end()) {

		(*it)->UpdateTarget(sf::Vector2f(this->player->posX, this->player->posY));
		(*it)->weapon->UpdateOrigineProjectile(sf::Vector2f((*it)->posX, (*it)->posY));

		float nextX = (*it)->GetNextMovementX() * this->deltaTime * 10000 * (*it)->speed;
		float nextY = (*it)->GetNextMovementY() * this->deltaTime * 10000 * (*it)->speed;
		(*it)->UpdatePos(nextX, nextY);

		if (!(*it)->IsOnColliderWithEnemy(this->listEnemy)) {
			(*it)->PerformAction(this->deltaTime);
		}

		(*it)->UpdatePos(-nextX, -nextY);

		it++;
	}
}

void Game::AllEnemyShoot()
{
	std::list<Enemy*>::iterator it = this->listEnemy.begin();
	while (it != this->listEnemy.end()) {
		(*it)->weapon->Shoot(sf::Vector2f(this->player->posX,this->player->posY),&this->listProjectile, PROJETILE_OF::ENEMY);
		it++;
	}
}

void Game::MoveAllProjectiles()
{
	std::list<Projectile*>::iterator it = this->listProjectile.begin();
	while (it != this->listProjectile.end()) {
		(*it)->MoveProjectile(this->deltaTime);
		it++;
	}
}

void Game::CollisionProjectile() {

	std::list<Projectile*>::iterator it = this->listProjectile.begin();
	std::list<Enemy*>::iterator it2;
	std::list<Brique*>::iterator it3;
	bool projectRemove = false;
	while (it != this->listProjectile.end()) {

		projectRemove = false;
		if ((*it)->projectileOf == PROJETILE_OF::PLAYER) {
			it2 = this->listEnemy.begin();
			while (it2 != this->listEnemy.end()) {
				if (it == this->listProjectile.end()) {
					return;
				}
				else if (IsOnCollider((*it)->projectile.getGlobalBounds(), (*it2)->rectangle.getGlobalBounds())) {

					(*it2)->TakeDommage((*it)->weaponDamage);

					(*it)->~Projectile();
					projectRemove = true;
					it = listProjectile.erase(it);
				}

				if ((*it2)->vie <= 0) {
					(*it2)->~Enemy();
					it2 = listEnemy.erase(it2);
				}
				else {
					it2++;
				}
			}
		}

		it3 = this->arena->briques.begin();
		while (it3 != this->arena->briques.end() && !projectRemove) {
			if (it == this->listProjectile.end()) {
				return;
			} else if (IsOnCollider((*it)->projectile.getGlobalBounds(), (*it3)->rectangle.getGlobalBounds())) {
				(*it)->~Projectile();
				projectRemove = true;
				it = listProjectile.erase(it);
			}
			it3++;
		}

		if (!projectRemove && (*it)->projectileOf == PROJETILE_OF::ENEMY && IsOnCollider((*it)->projectile.getGlobalBounds(), this->player->cercle.getGlobalBounds()) ) {
			this->player->TakeDommage((*it)->weaponDamage);
			(*it)->~Projectile();
			projectRemove = true;
			it = listProjectile.erase(it);
		}

		if ( this->player->vie <= 0 ) {
			this->player->SetTypeMovment(ACTION::DEAD);
		}

		if (!projectRemove) {
			it++;
		}

	}
}

void Game::CollisionEnemy() {

	std::list<Enemy*>::iterator it = this->listEnemy.begin();
	while (it != this->listEnemy.end()) {

		if ( IsOnCollider((*it)->rectangle.getGlobalBounds(),this->player->cercle.getGlobalBounds()) ) {
			this->player->TakeDommage((*it)->weapon->weaponDamage);
			if (this->player->vie <= 0) {
				this->player->SetTypeMovment(ACTION::DEAD);
			}
			(*it)->~Enemy();
			it = this->listEnemy.erase(it);
		}
		else {
			it++;
		}

	}
}

bool Game::IsOnCollider(sf::FloatRect firstRect, sf::FloatRect secondeRect)
{
	if (firstRect.intersects(secondeRect)) {
		return true;
	}
	return false;
}

float Clamp(float f, float limitMax, float limitMin) {
	if (Abs(f) > limitMax) {
		f = (float)limitMax * (f / Abs(f));
	} else if (Abs(f) < limitMin) {
		f = (float)limitMin * (f / Abs(f));
	}
	return f;
}

float Abs(float f) {
	return f > 0 ? f : -f;
}
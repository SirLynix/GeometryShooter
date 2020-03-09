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
#include "Arc.h"
#include "Grenade.h"
#include "Heal.h"
#include "PowerUp.h"

const int thicknessesBrique = 10;
const int thicknessesEnemy = 50;

Game::Game(Player* _player, int height, int width) : player(_player)
{
	srand(time(NULL));
	sf::Vector2f nbTiles = sf::Vector2f(38, 21);
	this->arena = new Arena(height, width, thicknessesBrique, nbTiles, 50);
	this->deltaTime = 0;
	this->totalTime = 0;

	Weapon* newWeapon = new MachineGun();
	newWeapon->UpdateOrigineProjectile(sf::Vector2f(200, 200));
	this->listWeapon.push_back(newWeapon);

	Weapon* newWeapon2 = new ShotGun();
	newWeapon2->UpdateOrigineProjectile(sf::Vector2f(1600, 200));
	this->listWeapon.push_back(newWeapon2);

	Weapon* newWeapon3 = new GrenadeLauncher();
	newWeapon3->UpdateOrigineProjectile(sf::Vector2f(200, 1000));
	this->listWeapon.push_back(newWeapon3);


	//PowerUp* newPowerUp = new Heal(200, 300, this->fontForText, 1);
	//this->listpowerUp.push_back(newPowerUp);
}

void Game::AddEnemy(Enemy* enemyToAdd)
{
	listEnemy.push_back(enemyToAdd);
}

void Game::RemoveEnemy(Enemy* enemyToRemove)
{
	listEnemy.remove(enemyToRemove);
}

void Game::DisplayGame(sf::RenderWindow* window)
{
	this->arena->DisplayArena(window);
	this->AutoCallWave(window);
	this->AutoCallWeapons(window);

	std::list<PowerUp*>::iterator it4 = this->listpowerUp.begin();
	while (it4 != this->listpowerUp.end()) {
		(*it4)->DisplayPowerUp(window);
		it4++;
	}

	this->player->DrawPlayer(window);

	std::list<Enemy*>::iterator it = this->listEnemy.begin();
	while (it != this->listEnemy.end()) {
		(*it)->DisplayEnemy(window);
		it++;
	}

	std::list<Weapon*>::iterator it3 = this->listWeapon.begin();
	while (it3 != this->listWeapon.end()) {
		(*it3)->DrawWeapon(window);
		it3++;
	}

	std::list<Projectile*>::iterator it2 = this->listProjectile.begin();
	while (it2 != this->listProjectile.end()) {
		(*it2)->DisplayProjectile(window);
		it2++;
	}

	this->player->DrawPlayer(window);

	window->draw(this->texteWinLose);

}

void Game::SpawnWeapons(sf::RenderWindow* window) {
	int borneMaxX = window->getSize().x - thicknessesEnemy / 2 - thicknessesBrique;
	int borneMaxY = window->getSize().y - thicknessesEnemy / 2 - thicknessesBrique;

	int borneMin = thicknessesEnemy / 2 + thicknessesBrique;

	int x, y;
	int typeWeapon;
	for (size_t i = 0; i < 2; i++)
	{
		Weapon* weapon = new Gun();
		typeWeapon = rand() % 3;
		switch (typeWeapon)
		{
		case 0:
			weapon = new ShotGun();
			break;
		case 1:
			weapon = new MachineGun();
			break;
		case 2:
			weapon = new GrenadeLauncher();
			break;
		}

		x = rand() % (borneMaxX + 1);
		y = rand() % (borneMaxY + 1);
		if (x < borneMin) {
			x = borneMin;
		}
		if (y < borneMin) {
			y = borneMin;
		}

		weapon->UpdateOrigineProjectile(sf::Vector2f(x, y));
		this->listWeapon.push_back(weapon);
	}
}

void Game::CreateWave(int nbZombie, int nbArcher, sf::RenderWindow* window)
{
	int borneMaxX = window->getSize().x - thicknessesEnemy / 2 - thicknessesBrique;
	int borneMaxY = window->getSize().y - thicknessesEnemy / 2 - thicknessesBrique;

	int borneMin = thicknessesEnemy / 2 + thicknessesBrique;

	int x;
	int y;
	bool enemiSpawn = false;
	int nbEssaieSpawn = 0;
	for (int i = 0; i < nbZombie; i++)
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
			Enemy* enemyZombie = new Zombie(x, y, thicknessesEnemy, new Weapon(1, 2, -1, 999, ""));
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
			Enemy* enemyArcher = new Archer(x, y, thicknessesEnemy, new Arc());
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
	this->timeBeforeCallNewWave -= _deltaTime;
	this->player->PerformAction(this->arena, this->listEnemy, deltaTime);
	this->player->weapon->UpdateFireRate(deltaTime);

	UpdateDash();

	std::list<Enemy*>::iterator it = this->listEnemy.begin();
	while (it != this->listEnemy.end()) {
		(*it)->weapon->UpdateFireRate(_deltaTime);
		it++;
	}


	std::list<Projectile*>::iterator it2 = this->listProjectile.begin();
	while (it2 != this->listProjectile.end()) {
		if ((*it2)->canExplode)
		{
			(*it2)->UpdateRadius(_deltaTime);

		}
		if ((*it2)->explosionCooldown > -1.0f)
		{
			(*it2)->UpdateExplosionCooldown(_deltaTime);
		}
		it2++;
	}

}

void Game::UpdateDash()
{
	if (this->player->isDashing && this->player->dashDuration > 0.f) {
		this->player->dashDuration -= deltaTime;

		ACTION ty = this->player->typeMovement;
		if (ty == ACTION::UP_LEFT || ty == ACTION::UP_RIGHT || ty == ACTION::DOWN_LEFT || ty == ACTION::DOWN_RIGHT) {
			this->player->speed = ((this->player->dashFactor * this->player->baseSpeed) - (2000.f * (.2f - this->player->dashDuration))) / sqrt(2);
		} else {
			this->player->speed = ((this->player->dashFactor * this->player->baseSpeed) - (2000.f * (.2f - this->player->dashDuration)));
		}

	} else {
		this->player->speed = this->player->baseSpeed;
		this->player->isDashing = false;
		this->player->dashDuration = .2f;

		if (this->player->dashCD > 0.f && !this->player->canDash) {
			this->player->dashCD -= deltaTime;
			this->player->dashCDUI.setScale(sf::Vector2f(this->player->dashCD / this->player->baseCD, 1));
		} else {
			this->player->dashCD = this->player->baseCD;
			this->player->dashCDUI.setScale(sf::Vector2f(this->player->dashCD / this->player->baseCD, 1));
			this->player->canDash = true;
		}
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
		(*it)->UpdatePos(nextX, 0);

		if ((*it)->IsOnColliderWithEnemy(this->listEnemy)) {
			(*it)->moveOnX = false;
		}
		else {
			(*it)->moveOnX = true;
		}

		(*it)->UpdatePos(-nextX, 0);
		(*it)->UpdatePos(0, nextY);

		if ((*it)->IsOnColliderWithEnemy(this->listEnemy)) {
			(*it)->moveOnY = false;
		}
		else {
			(*it)->moveOnY = true;
		}
		(*it)->UpdatePos(0, -nextY);
		(*it)->PerformAction(this->deltaTime);

		it++;
	}
}

void Game::AllEnemyShoot()
{
	std::list<Enemy*>::iterator it = this->listEnemy.begin();
	while (it != this->listEnemy.end()) {
		(*it)->weapon->Shoot(sf::Vector2f(this->player->posX, this->player->posY), &this->listProjectile, PROJECTILE_OF::ENEMY);
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
		if ((*it)->toDestruct)
		{
			(*it)->~Projectile();
			it = listProjectile.erase(it);
			projectRemove = true;
		}
		if (it != this->listProjectile.end() && (*it)->projectileOf == PROJECTILE_OF::PLAYER) {
			it2 = this->listEnemy.begin();
			while (it2 != this->listEnemy.end()) {
				if (it == this->listProjectile.end()) {
					return;
				} else if (IsOnCollider((*it)->projectile.getGlobalBounds(), (*it2)->rectangle.getGlobalBounds())) {

					(*it2)->TakeDommage((*it)->weaponDamage);

					if ((*it)->typeProjectile == TYPE_PROJECTILE::BULLET)
					{
						(*it)->~Projectile();
						projectRemove = true;
						it = listProjectile.erase(it);
					} else if ((*it)->typeProjectile == TYPE_PROJECTILE::GRENADE && (*it)->explosionCooldown < 0.0f)
					{
						(*it)->SetExplosionSettings();
						(*it)->canExplode = true;

					}
					(*it2)->UpdateUiToPv();
				}

				if ((*it2)->vie <= 0) {
					(*it2)->~Enemy();
					it2 = listEnemy.erase(it2);
				} else {
					it2++;
				}
			}
		}

		it3 = this->arena->briques.begin();
		while (it3 != this->arena->briques.end() && !projectRemove) {
			if (it == this->listProjectile.end()) {
				return;
			} else if ((*it)->typeProjectile == TYPE_PROJECTILE::GRENADE && IsOnCollider((*it)->projectile.getGlobalBounds(), (*it3)->rectangle.getGlobalBounds())) {
				(*it)->canExplode = true;
				(*it)->SetExplosionSettings();
			} else if (IsOnCollider((*it)->projectile.getGlobalBounds(), (*it3)->rectangle.getGlobalBounds()))
			{
				(*it)->~Projectile();
				projectRemove = true;
				it = listProjectile.erase(it);
			}
			it3++;
		}


		if (!projectRemove && (*it)->projectileOf == PROJECTILE_OF::ENEMY && IsOnCollider((*it)->projectile.getGlobalBounds(), this->player->cercle.getGlobalBounds())) {
			this->player->TakeDommage((*it)->weaponDamage);
			(*it)->~Projectile();
			projectRemove = true;
			it = listProjectile.erase(it);
		}

		if (this->player->vie <= 0) {
			this->player->SetTypeMovment(ACTION::DEAD);
			this->texteWinLose.setString("YOU DIED");
			this->texteWinLose.setCharacterSize(100);
			this->texteWinLose.setOrigin(220, 70);
			this->texteWinLose.setPosition(this->player->posX, this->player->posY);
			this->texteWinLose.setFillColor(sf::Color::Red);
		}

		if (!projectRemove) {
			it++;
		}

	}
}

void Game::CollisionEnemy() {

	std::list<Enemy*>::iterator it = this->listEnemy.begin();
	while (it != this->listEnemy.end()) {

		if (IsOnCollider((*it)->rectangle.getGlobalBounds(), this->player->cercle.getGlobalBounds())) {
			this->player->TakeDommage((*it)->weapon->weaponDamage);
			if (this->player->vie <= 0) {
				this->player->SetTypeMovment(ACTION::DEAD);
			}
			(*it)->~Enemy();
			it = this->listEnemy.erase(it);
		} else {
			it++;
		}

	}
}

void Game::CollisionPlayer() {

	std::list<Weapon*>::iterator it = this->listWeapon.begin();
	while (it != this->listWeapon.end()) {

		if (IsOnCollider((*it)->rectangle.getGlobalBounds(), this->player->cercle.getGlobalBounds())) {
			this->player->weapon->~Weapon();
			this->player->SetWeapon((*it));
			it = this->listWeapon.erase(it);
		} else {
			it++;
		}

	}

	std::list<PowerUp*>::iterator it2 = this->listpowerUp.begin();
	while (it2 != this->listpowerUp.end()) {

		if (IsOnCollider((*it2)->circle.getGlobalBounds(), this->player->cercle.getGlobalBounds())) {
			(*it2)->ApplyPowerUp(this->player);
			it2 = this->listpowerUp.erase(it2);
		} else {
			it2++;
		}

	}
}

void Game::UpdateGame() {
	this->MoveAllEnemy();
	this->AllEnemyShoot();
	this->MoveAllProjectiles();
	this->CollisionPlayer();
	this->CollisionProjectile();
	this->CollisionEnemy();
	this->CheckForNewWave();
	this->CheckForNewWeapons();
	this->CheckForWin();
}

void Game::AutoCallWeapons(sf::RenderWindow* window) {
	if (changeWeapons && timeBeforeNewWeapons < 0.f) {
		changeWeapons = false;
		SpawnWeapons(window);
	}
}
void Game::AutoCallWave(sf::RenderWindow* window)
{
	if (changeWave && timeBeforeCallNewWave < 0.0f) {
		changeWave = false;
		nbWave++;
		if (nbWave == 1) {
			CreateWave(2, 0, window);
		}
		if (nbWave == 2) {
			CreateWave(0, 2, window);
		}
		if (nbWave == 3) {
			CreateWave(5, 0, window);
		}
		if (nbWave == 4) {
			CreateWave(0, 5, window);
		}
		if (nbWave == 5) {
			CreateWave(5, 5, window);
		}
		if (nbWave == 6) {
			CreateWave(10, 10, window);
		}
	}
}

void Game::CheckForNewWave()
{
	if (this->listEnemy.empty() && !changeWave) {
		changeWave = true;
		timeBeforeCallNewWave = 5.0f;
	}
}

void Game::CheckForNewWeapons() {
	if (timeBeforeNewWeapons < 0.f && !changeWeapons) {
		changeWeapons = true;
		timeBeforeNewWeapons = 15.f;
	} else {
		timeBeforeNewWeapons -= deltaTime;
	}
}

void Game::CheckForWin()
{
	if (this->listEnemy.empty() && this->nbWave >= 6 && this->player->vie > 0) {
		this->texteWinLose.setString("VICTORY");
		this->texteWinLose.setCharacterSize(100);
		this->texteWinLose.setOrigin(220, 70);
		this->texteWinLose.setPosition(this->player->posX, this->player->posY);
		this->texteWinLose.setFillColor(sf::Color::Red);
	}
}

bool Game::IsOnCollider(sf::FloatRect firstRect, sf::FloatRect secondeRect)
{
	if (firstRect.intersects(secondeRect)) {
		return true;
	}
	return false;
}
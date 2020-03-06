#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Character.h";
#include "Arena.h";
#include "Player.h";
#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "Shotgun.h"
#include "MachineGun.h"
#include "Gun.h"
#include "GrenadeLauncher.h"
#include "PowerUp.h"

using namespace std;

class Game
{
public:
	Player* player;
	list <Enemy*> listEnemy;
	list <Projectile*> listProjectile;
	list <Weapon*> listWeapon;
	list <PowerUp*> listpowerUp;
	Arena* arena;
	sf::RenderWindow* window;
	sf::Font* fontForText;
	float deltaTime;
	float totalTime;
	float timeBeforeCallNewWave = -1;
	bool changeWave = false;
private:
	int nbWave = 0;

public:
	Game(Player* _player, int height, int width, sf::RenderWindow* _window, std::string _fontForText);
	void AddEnemy(Enemy* enemyToAdd);
	void RemoveEnemy(Enemy* enemyToRemove);
	void DisplayGame();
	void CreateWave(int nbZombie, int nbArcher);
	void UpdateTime(float _deltaTime);
	void UpdateDash();
	void MoveAllEnemy();
	void CollisionEnemy();
	void MoveAllProjectiles();
	void CollisionProjectile();
	void CollisionPlayer();
	bool IsOnCollider(sf::FloatRect firstRect, sf::FloatRect secondeRect);
	void AllEnemyShoot();
	void UpdateGame();
	void AutoCallWave();
	void CheckForNewWave();
};
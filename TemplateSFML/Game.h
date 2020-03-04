#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Character.h";
#include "Arena.h";
#include "Player.h";
#include "Enemy.h"

using namespace std;

class Game
{
public:
	Player* player;
	list <Enemy*> listEnemy;
	list <Projectile*> listProjectile;
	Arena* arena;
	sf::RenderWindow* window;
	float deltaTime;
	float totalTime;

public:
	Game(Player* _player, int height, int width, sf::RenderWindow* _window);
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
	bool IsOnCollider(sf::FloatRect firstRect, sf::FloatRect secondeRect);
	void AllEnemyShoot();
};
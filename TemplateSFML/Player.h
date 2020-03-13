#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Arena.h"
#include "Enemy.h"

enum class ACTION
{
	UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT, DEAD, NONE
};

class Player : public Character
{
public:
	bool hasBulletTime = false;
	bool canMove = true;
	bool isDashing = false;
	bool canDash;
	bool onBulletTime = false;
	float bulletTimeDuration = 0.0f;
	float dashFactor;
	float baseSpeed;
	float dashDuration;
	float dashCD = 0.0f;
	float baseCD = 0.0f;
	sf::CircleShape cercle;
	ACTION typeMovement;
	sf::CircleShape spawnCircle;
	std::list<ACTION> listAction;


public:
	Player(int _posX, int _posY, Weapon* weapon);
	void Dash();
	void DrawPlayer(sf::RenderWindow* window);
	void PerformAction(Arena* arene, std::list<Enemy*> listEnemy, float _deltaTime);
	void MoveTo(float _posX, float _posY) override;
	void addAction(ACTION actionToAdd);
	void removeAction(ACTION actionToDel);
	void UpdateDirectionMovement();
	void SetTypeMovment(ACTION _newAction);
	void SetWeapon(Weapon* weapon);
	void RotationPlayer(float angleRotation);
	void FeedbackDamageTaken(float _deltaTime);
private:
	void UpdateCerclePos();
};
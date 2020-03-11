#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Character.h"
#include "Brique.h"

const float OffsetPosXOfPV = 5;
const float OffsetPosYOfPV = 15;

class Enemy : public Character
{
public:
	sf::RectangleShape rectangle;
	sf::RectangleShape pv1;
	sf::RectangleShape pv2;
	sf::RectangleShape pv3;
	sf::Vector2f target;
	bool moveOnX = true;
	bool moveOnY = true;
public:
	Enemy(float _posX, float _poxY, int thicknessesEnemy, Weapon* weapon, int vie, float speed);
	virtual void DisplayEnemy(sf::RenderWindow* window);
	void UpdateTarget(sf::Vector2f newTarget);
	void UpdatePos(float x, float y);
	virtual void UpdateUiToPv();
	bool IsOnColliderWithEnemy(std::list<Enemy*> listEnemy);
	bool IsOnColliderWithBrique(std::list<Brique*> listBrique);
	virtual void PerformAction(float _deltaTime);
	virtual float GetNextMovementX();
	virtual float GetNextMovementY();
	void FeedbackDamageTaken(float _deltaTime);

protected:
	void UpdateEnemyPos();
	virtual void UpdatePositionUiPv();
};
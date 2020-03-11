#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <vector>

class Tank : public Enemy
{
public: 
	std::vector<sf::RectangleShape*> tabHp;
public:
	Tank(float _posX, float _posY, int thicknessesEnemy, Weapon* weapon);
	void PerformAction(float _deltaTime) override;
	float GetNextMovementX();
	float GetNextMovementY();
	void UpdateUiToPv();
	void DisplayEnemy(sf::RenderWindow* window);
	void UpdatePositionUiPv();
};


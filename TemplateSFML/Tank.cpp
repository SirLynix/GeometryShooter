#include "Tank.h"

Tank::Tank(float _posX, float _posY, int thicknessesEnemy, Weapon* weapon) : Enemy(_posX, _posY, thicknessesEnemy, weapon, 9, 1.0f) 
{
	this->rectangle.setFillColor(sf::Color::Yellow);

	this->tabHp.resize(this->vie);

	for (int i = 0; i < this->vie; i++)
	{
		sf::RectangleShape* HP = new sf::RectangleShape();
		HP->setSize(sf::Vector2f(this->rectangle.getSize().x / 4, 5));
		HP->setOrigin(HP->getSize().x / 2, HP->getSize().y / 2);
		if (i/3 == 0)
		{
			HP->setFillColor(sf::Color::Red);
		}
		else if (i / 3 == 1)
		{
			HP->setFillColor(sf::Color(255, 140, 0));
		}
		else
		{
			HP->setFillColor(sf::Color::Green);
		}
		if (i % 3 == 0)
		{
			HP->setPosition(this->posX - HP->getSize().x - OffsetPosXOfPV, this->posY - this->rectangle.getSize().y + OffsetPosYOfPV);
		}
		else if (i % 3 == 1)
		{
			HP->setPosition(this->posX - HP->getSize().x, this->posY - this->rectangle.getSize().y + OffsetPosYOfPV);
		}
		else
		{
			HP->setPosition(this->posX - HP->getSize().x + OffsetPosXOfPV, this->posY - this->rectangle.getSize().y + OffsetPosYOfPV);
		}


		this->tabHp[i] = HP;
	}
}

void Tank::PerformAction(float _deltaTime)
{
	if (this->moveOnX) {
		this->MoveTo(this->speed * _deltaTime * 100 * GetNextMovementX(), 0);
	}
	if (this->moveOnY) {
		this->MoveTo(0, this->speed * _deltaTime * 100 * GetNextMovementY());
	}
}

float Tank::GetNextMovementX()
{
	float moveX = 0;

	float dist = sqrt(pow(this->target.x - this->posX, 2) + pow(this->target.y - this->posY, 2));

	if (dist > 20.f) {

		double angle = atan2(this->target.y - this->posY, this->target.x - this->posX);

		moveX = cos(angle);
	}

	return moveX;
}

float Tank::GetNextMovementY()
{
	float moveY = 0;

	float dist = sqrt(pow(this->target.x - this->posX, 2) + pow(this->target.y - this->posY, 2));

	if (dist > 20.f) {

		double angle = atan2(this->target.y - this->posY, this->target.x - this->posX);

		moveY = sin(angle);
	}
	return moveY;
}

void Tank::UpdateUiToPv()
{
	while (tabHp.size() > this->vie)
	{
		delete tabHp[tabHp.size() - 1];
		tabHp.resize(tabHp.size() - 1);
		}
	
}

void Tank::DisplayEnemy(sf::RenderWindow* window)
{
	Enemy::UpdateEnemyPos();
	window->draw(this->rectangle);
	
	for (int i = 0; i < tabHp.size(); i++)
	{
		window->draw(*tabHp[i]);
	}
}

void Tank::UpdatePositionUiPv()
{
	for(int i =0; i < tabHp.size();i++)
	{
		if (i % 3 == 0)
		{
			tabHp[i]->setPosition(this->posX - tabHp[i]->getSize().x - OffsetPosXOfPV, this->posY - this->rectangle.getSize().y + OffsetPosYOfPV);
		}
		else if (i % 3 == 1)
		{
			tabHp[i]->setPosition(this->posX, this->posY - this->rectangle.getSize().y + OffsetPosYOfPV);
		}
		else
		{
			tabHp[i]->setPosition(this->posX + tabHp[i]->getSize().x + OffsetPosXOfPV, this->posY - this->rectangle.getSize().y + OffsetPosYOfPV);
		}
	}
}

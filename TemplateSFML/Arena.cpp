#include "Arena.h"
#include "Brique.h"

Arena::Arena(int _width, int _height, int _thicknessesBrique, sf::Vector2f _nbTiles, int _tileSize) : width(_width), height(_height), thicknessesBrique(_thicknessesBrique), nbTiles(_nbTiles), tileSize(_tileSize) {
	CreateArena();
}

void Arena::CreateArena() {
	sf::RectangleShape*** echiquier = new sf::RectangleShape * *[nbTiles.x];
	for (size_t i = 0; i < nbTiles.x; i++)
	{
		echiquier[i] = new sf::RectangleShape * [nbTiles.y];

		for (size_t j = 0; j < nbTiles.y; j++)
		{
			echiquier[i][j] = new sf::RectangleShape{};
			sf::Color color = (i + j) % 2 == 0 ? sf::Color(0, 0, 0) : sf::Color(20, 20, 20);
			echiquier[i][j]->setFillColor(color);
			echiquier[i][j]->setSize(sf::Vector2f(50, 50));
			echiquier[i][j]->setPosition(sf::Vector2f(i * 50 + this->thicknessesBrique, j * 50 + this->thicknessesBrique));
		}
	}
	this->echiquier = echiquier;
	briques.push_back(new Brique(0, 0, SensBrique::HORIZONTAL, this->thicknessesBrique, this->height)); //LEFT
	briques.push_back(new Brique(this->width - this->thicknessesBrique, 0, SensBrique::HORIZONTAL, this->thicknessesBrique, this->height)); //RIGHT
	briques.push_back(new Brique(0, 0, SensBrique::VERTICAL, this->thicknessesBrique, this->width)); //TOP
	briques.push_back(new Brique(0, this->height - this->thicknessesBrique, SensBrique::VERTICAL, this->thicknessesBrique, this->width)); //BOTTM
}

void Arena::DisplayArena(sf::RenderWindow* window) {
	std::list<Brique*>::iterator it = briques.begin();
	while (it != briques.end()) {
		(*it)->DisplayBrique(window);
		it++;
	}
	for (size_t i = 0; i < window->getSize().x / this->tileSize; i++)
	{
		for (size_t j = 0; j < window->getSize().y / this->tileSize; j++)
		{
			window->draw(*(echiquier[i][j]));
		}
	}
}
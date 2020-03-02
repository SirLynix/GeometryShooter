#include "Arena.h"
#include "Brique.h"

Arena::Arena(int _width, int _height, int _thicknessesBrique, sf::RectangleShape*** _echiquier, int _nbTiles, int _tileSize) : width(_width), height(_height), thicknessesBrique(_thicknessesBrique), echiquier(_echiquier), nbTiles(_nbTiles), tileSize(_tileSize) {}

void Arena::CreateArena() {
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
	for (size_t i = 1; i < window->getSize().x / this->tileSize; i++)
	{
		for (size_t j = 1; j < window->getSize().y / this->tileSize; j++)
		{
			window->draw(*(echiquier[i][j]));
		}
	}
}
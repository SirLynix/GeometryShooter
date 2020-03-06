#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Brique.h";

using namespace std;

class Arena
{
public:
	int width;
	int height;
	list<Brique*> briques;
	int thicknessesBrique;
	sf::RectangleShape*** echiquier;
	sf::Vector2f nbTiles;
	int tileSize;

public:
	Arena(int _width, int _height, int _thicknessesBrique, sf::Vector2f _nbTiles, int _tileSize);
	void CreateArena();
	void DisplayArena(sf::RenderWindow* window);
};
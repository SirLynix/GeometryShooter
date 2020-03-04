// TemplateSFML.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Game.h"

using namespace std;
using namespace sf;
string getAppPath();
string getAssetPath();
void InputForMovePlayer(sf::Event event, Player* player);

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "ChronoSpacer");

	sf::View view(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Vector2f(window.getSize().x - 200, window.getSize().y - 200));
	window.setView(view);

	sf::Clock clock;
	sf::Mouse mouse;

	Game* game = new Game(new Player(window.getSize().x / 2, window.getSize().y / 2, new Gun()), window.getSize().x, window.getSize().y, &window);

	float deltaTime;

	// Initialise everything below
	// Game loop
	while (window.isOpen()) {

		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window.close();
			}

			InputForMovePlayer(event, game->player);

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
				game->player->RotationPlayer(90);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
				game->player->RotationPlayer(-90);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
				game->CreateWave(5, 5);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
				game->CreateWave(0, 5);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
				game->CreateWave(5, 0);
			}

		}

		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(mouse.getPosition(window).x, mouse.getPosition(window).y));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && game->player->typeMovement != ACTION::DEAD) {
			game->player->weapon->Shoot(mousePos, &game->listProjectile, PROJETILE_OF::PLAYER);
		}

		double angle = atan2(mousePos.y - game->player->cercle.getPosition().y, mousePos.x - game->player->cercle.getPosition().x);

		game->player->RotationPlayer(angle);

		game->UpdateTime(deltaTime);
		game->UpdateGame();

		view.setCenter(game->player->posX, game->player->posY);
		window.setView(view);

		window.clear();
		// Whatever I want to draw goes here
		game->DisplayGame();
		window.display();
	}
}

string getAppPath() {
	char cExeFilePath[256];
	GetModuleFileNameA(NULL, cExeFilePath, 256);
	string exeFilePath = cExeFilePath;
	int exeNamePos = exeFilePath.find_last_of("\\/");
	return exeFilePath.substr(0, exeNamePos + 1);
}

string getAssetPath() {
	string path = getAppPath();
	return path + "Assets";
}

void InputForMovePlayer(sf::Event event, Player* player) {
	if (event.type == event.KeyPressed) {
		if (event.key.code == sf::Keyboard::Z) {
			if (!player->CheckForMovement(ACTION::UP)) {
				player->SetTypeMovment(ACTION::IDLE);
			}
			else if (player->typeMovement == ACTION::NONE) {
				player->SetTypeMovment(ACTION::UP);
			}
			else {
				player->SetComboMovement(ACTION::UP);
			}
		}

		if (event.key.code == sf::Keyboard::S) {
			if (!player->CheckForMovement(ACTION::DOWN)) {
				player->SetTypeMovment(ACTION::IDLE);
			}
			else if (player->typeMovement == ACTION::NONE) {
				player->SetTypeMovment(ACTION::DOWN);
			}
			else {
				player->SetComboMovement(ACTION::DOWN);
			}
		}

		if (event.key.code == sf::Keyboard::Q) {
			if (!player->CheckForMovement(ACTION::LEFT)) {
				player->SetTypeMovment(ACTION::IDLE);
			}
			else if (player->typeMovement == ACTION::NONE) {
				player->SetTypeMovment(ACTION::LEFT);
			}
			else {
				player->SetComboMovement(ACTION::LEFT);
			}
		}

		if (event.key.code == sf::Keyboard::D) {
			if (!player->CheckForMovement(ACTION::RIGHT)) {
				player->SetTypeMovment(ACTION::IDLE);
			}
			else if (player->typeMovement == ACTION::NONE) {
				player->SetTypeMovment(ACTION::RIGHT);
			}
			else {
				player->SetComboMovement(ACTION::RIGHT);
			}
		}
	}
	if (event.type == event.KeyReleased) {

		if (event.key.code == sf::Keyboard::Z) {
			if (player->typeMovement == ACTION::UP) {
				player->SetTypeMovment(ACTION::NONE);
			}
			else if (player->typeMovement == ACTION::UP_LEFT) {
				player->SetTypeMovment(ACTION::LEFT);
			}
			else if (player->typeMovement == ACTION::UP_RIGHT) {
				player->SetTypeMovment(ACTION::RIGHT);
			}
			else if (player->typeMovement == ACTION::IDLE) {
				player->SetTypeMovment(ACTION::DOWN);
			}
		}

		if (event.key.code == sf::Keyboard::S) {
			if (player->typeMovement == ACTION::DOWN) {
				player->SetTypeMovment(ACTION::NONE);
			}
			else if (player->typeMovement == ACTION::DOWN_LEFT) {
				player->SetTypeMovment(ACTION::LEFT);
			}
			else if (player->typeMovement == ACTION::DOWN_RIGHT) {
				player->SetTypeMovment(ACTION::RIGHT);
			}
			else if (player->typeMovement == ACTION::IDLE) {
				player->SetTypeMovment(ACTION::UP);
			}
		}

		if (event.key.code == sf::Keyboard::Q) {
			if (player->typeMovement == ACTION::LEFT) {
				player->SetTypeMovment(ACTION::NONE);
			}
			else if (player->typeMovement == ACTION::DOWN_LEFT) {
				player->SetTypeMovment(ACTION::DOWN);
			}
			else if (player->typeMovement == ACTION::UP_LEFT) {
				player->SetTypeMovment(ACTION::UP);
			}
			else if (player->typeMovement == ACTION::IDLE) {
				player->SetTypeMovment(ACTION::RIGHT);
			}
		}

		if (event.key.code == sf::Keyboard::D) {
			if (player->typeMovement == ACTION::RIGHT) {
				player->SetTypeMovment(ACTION::NONE);
			}
			else if (player->typeMovement == ACTION::DOWN_RIGHT) {
				player->SetTypeMovment(ACTION::DOWN);
			}
			else if (player->typeMovement == ACTION::UP_RIGHT) {
				player->SetTypeMovment(ACTION::UP);
			}
			else if (player->typeMovement == ACTION::IDLE) {
				player->SetTypeMovment(ACTION::LEFT);
			}
		}

	}
}
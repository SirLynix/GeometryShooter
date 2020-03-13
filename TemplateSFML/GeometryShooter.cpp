// TemplateSFML.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Game.h"
#include "Player.h"
#include "Weapon.h"
#include "Shotgun.h"
#include "MachineGun.h"
#include "Gun.h"
#include "GrenadeLauncher.h"
#include "UI.h"
#include "ShakeScreen.h";

using namespace std;
using namespace sf;
string getAppPath();
string getAssetPath();
void InputForMovePlayer(sf::Event event, Player* player);

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "ChronoSpacer", Style::Fullscreen);

	sf::View view(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Vector2f(window.getSize().x - 200, window.getSize().y - 200));

	sf::Clock clock;
	sf::Mouse mouse;

	Game* game = new Game(new Player(window.getSize().x / 2, window.getSize().y / 2, new Gun()), window.getSize().x, window.getSize().y);
	UI* ui = new UI(&window, getAssetPath() + "\\retro.ttf", game);
	ShakeScreen* shakeScreen = new ShakeScreen(&view, game->player->cercle.getPosition());

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

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && game->player->typeMovement != ACTION::DEAD && game->player->typeMovement != ACTION::NONE) {
				game->player->Dash();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				game->Restart(ui->window->getSize().x / 2, ui->window->getSize().y / 2);
			}

		}

		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(mouse.getPosition(window).x, mouse.getPosition(window).y));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && game->player->typeMovement != ACTION::DEAD) {

			if (game->player->weapon->ammo < 1) {
				game->player->weapon = new Gun();
				game->player->weapon->cooldownFirerate = game->player->weapon->fireRate;
			}

			if (game->player->isAkimbo) {
				float newFR = game->player->weapon->fireRate / 2.f;
				int nbProj = game->listProjectile.size();

				if (game->player->akimboLeft) {
					game->player->akimbo->Shoot(mousePos, &game->listProjectile, PROJECTILE_OF::PLAYER);
					if (game->listProjectile.size() > nbProj) {
						game->player->akimboLeft ^= true;
						game->player->weapon->cooldownFirerate = newFR;
					}

				} else {
					game->player->weapon->Shoot(mousePos, &game->listProjectile, PROJECTILE_OF::PLAYER);
					if (game->listProjectile.size() > nbProj) {
						game->player->akimboLeft ^= true;
						game->player->akimbo->cooldownFirerate = newFR;
					}
				}
			} else {
				game->player->weapon->Shoot(mousePos, &game->listProjectile, PROJECTILE_OF::PLAYER);
			}

			if (game->player->weapon->cooldownFirerate == game->player->weapon->fireRate) {
				shakeScreen->shakeSreen = true;
				shakeScreen->UpdateAmplitude(game->player->weapon->amplitudeShakeScreen);
				shakeScreen->UpdateTimeShake(game->player->weapon->timeShake);
			}

		}

		if (game->player->typeMovement != ACTION::DEAD) {
			double angle = atan2(mousePos.y - game->player->cercle.getPosition().y, mousePos.x - game->player->cercle.getPosition().x);

			game->player->RotationPlayer(angle);
		}

		game->UpdateTime(deltaTime);
		if (shakeScreen->shakeSreen) {
			shakeScreen->UpdateCooldown(deltaTime);
		}
		game->UpdateGame();
		ui->UpdatePosUI();
		ui->UpdateHpPlayerUI();

		shakeScreen->UpdateOrigine(game->player->cercle.getPosition());

		shakeScreen->CheckForShake();

		window.setView(view);

		window.clear();

		game->DisplayGame(ui->window);
		ui->DisplayUI();

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
			player->addAction(ACTION::UP);
		}

		if (event.key.code == sf::Keyboard::S) {
			player->addAction(ACTION::DOWN);
		}

		if (event.key.code == sf::Keyboard::Q) {

			player->addAction(ACTION::LEFT);

		}

		if (event.key.code == sf::Keyboard::D) {
			player->addAction(ACTION::RIGHT);
		}
	}
	if (event.type == event.KeyReleased) {

		if (event.key.code == sf::Keyboard::Z) {
			player->removeAction(ACTION::UP);
		}

		if (event.key.code == sf::Keyboard::S) {
			player->removeAction(ACTION::DOWN);
		}

		if (event.key.code == sf::Keyboard::Q) {
			player->removeAction(ACTION::LEFT);
		}

		if (event.key.code == sf::Keyboard::D) {
			player->removeAction(ACTION::RIGHT);
		}

	}
}
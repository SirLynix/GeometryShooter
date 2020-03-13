#include "UI.h"
#include "Game.h"
UI::UI(sf::RenderWindow* window, sf::String fontForText, Game* game) : window(window), game(game)
{
	this->fontForText = new sf::Font;
	this->fontForText->loadFromFile(fontForText);

	this->texteWinLose.setFont(*this->fontForText);
	this->texteWinLose.setCharacterSize(100);
	this->texteWinLose.setOrigin(0, 0);
	this->texteWinLose.setFillColor(sf::Color::Red);

	this->UIRectangle = new sf::RectangleShape;
	this->vie = new sf::Text;
	this->vie->setFont(*this->fontForText);
	this->selectedWeapon = new sf::Text;
	this->selectedWeapon->setFont(*this->fontForText);

	this->dashCDUI = sf::RectangleShape();
	this->baseCDUI = sf::RectangleShape();
	this->dashCDUI.setSize(sf::Vector2f(180, 30));
	this->baseCDUI.setSize(sf::Vector2f(180, 30));
	this->dashCDUI.setFillColor(sf::Color(0, 255, 0));
	this->baseCDUI.setFillColor(sf::Color::White);

	this->UIRectangle->setSize(sf::Vector2f(550.0f, 100.0f));
	this->UIRectangle->setOrigin(sf::Vector2f(0.0f, 0.0f));
	this->UIRectangle->setFillColor(sf::Color(0, 0, 0, 120));
	this->UIRectangle->setOutlineColor(sf::Color::White);
	this->UIRectangle->setOutlineThickness(2);

	this->vie->setString(sf::String("Vie : "));
	this->vie->setCharacterSize(25);

	this->selectedWeapon->setCharacterSize(25);

	this->ammo = new sf::Text;
	this->ammo->setFont(*this->fontForText);

	std::list<PowerUp*>::iterator it = this->game->listpowerUp.begin();
	while (it != this->game->listpowerUp.end()) {
		(*it)->namePowerUp.setFont(*this->fontForText);
		it++;
	}

	this->textNextWave.setFont(*this->fontForText);
	this->textNextWave.setCharacterSize(25);
	this->textNextWave.setOrigin(0, 0);
	this->textNextWave.setFillColor(sf::Color::White);

	this->textNextWaveCountdown.setFont(*this->fontForText);
	this->textNextWaveCountdown.setCharacterSize(25);
	this->textNextWaveCountdown.setOrigin(0, 0);
	this->textNextWaveCountdown.setFillColor(sf::Color::White);
}


void UI::DisplayUI()
{
	this->window->draw(*this->UIRectangle);
	this->window->draw(*this->vie);

	this->ammo->setString(to_string(game->player->weapon->ammo));
	this->window->draw(*this->ammo);
	this->window->draw(*this->selectedWeapon);
	window->draw(this->baseCDUI);
	window->draw(this->dashCDUI);
	this->UpdateHpPlayerUI();

	std::list<sf::CircleShape*>::iterator it2 = this->listVies.begin();

	while (it2 != this->listVies.end())
	{
		this->window->draw(*(*it2));
		it2++;
	}

	CheckForWinAndLose();
	this->window->draw(this->texteWinLose);
	window->draw(textNextWave);
	window->draw(textNextWaveCountdown);
	CheckForNextWave();
	return;
}

void UI::UpdateHpPlayerUI()
{
	int differenceNbVies = game->player->vie - listVies.size();
	std::list<sf::CircleShape*>::iterator it2 = this->listVies.end();

	while (differenceNbVies < 0 && listVies.size() > 0)
	{
		it2--;
		it2 = this->listVies.erase(it2);
		differenceNbVies++;
	}

	while (differenceNbVies > 0)
	{
		sf::CircleShape* newCircle = new sf::CircleShape;
		newCircle->setRadius(15);
		newCircle->setFillColor(sf::Color::Green);
		newCircle->setOrigin(sf::Vector2f(0.0f, 0.0f));
		this->listVies.push_back(newCircle);
		differenceNbVies--;
	}
}

void UI::UpdatePosUI()
{
	float offset = this->UIRectangle->getSize().y + this->UIRectangle->getOutlineThickness();
	this->UIRectangle->setPosition(sf::Vector2f(this->game->player->posX - this->window->getSize().x / 2 + offset, this->game->player->posY - this->window->getSize().y / 2 + offset));

	this->UIRectangle->setFillColor(sf::Color(0, 0, 0, 120));
	this->UIRectangle->setOutlineColor(sf::Color::White);
	this->UIRectangle->setOutlineThickness(2);

	this->vie->setString(sf::String("Vie : "));
	this->vie->setCharacterSize(25);
	this->vie->setPosition(sf::Vector2f(this->UIRectangle->getPosition().x + 20.0f, this->UIRectangle->getPosition().y + 50.0f));
	this->selectedWeapon->setString(this->game->player->weapon->name.getString());
	this->selectedWeapon->setPosition(sf::Vector2f(this->UIRectangle->getPosition().x + 20.0f, this->UIRectangle->getPosition().y + 10.0f));

	this->ammo->setFillColor(sf::Color::White);
	this->ammo->setCharacterSize(25);
	this->ammo->setPosition(sf::Vector2f(this->UIRectangle->getPosition().x + 450.0f, this->UIRectangle->getPosition().y + 10.0f));

	float UiX = 0.0f;

	std::list<sf::CircleShape*>::iterator it2 = this->listVies.begin();

	while (it2 != this->listVies.end())
	{
		(*it2)->setPosition(this->UIRectangle->getPosition().x + 100.0f + UiX, this->UIRectangle->getPosition().y + 52.0f);
		this->window->draw(*(*it2));
		it2++;
		UiX += 50.0f;
	}

	float offX = 330.0f;
	float offY = 52.0f;
	this->baseCDUI.setPosition(sf::Vector2f(this->UIRectangle->getPosition().x + offX, this->UIRectangle->getPosition().y + offY));
	this->dashCDUI.setPosition(sf::Vector2f(this->UIRectangle->getPosition().x + offX, this->UIRectangle->getPosition().y + offY));

	if (game->player->dashCD > 0.f && !game->player->canDash) {
		this->dashCDUI.setScale(sf::Vector2f(game->player->dashCD / game->player->baseCD, 1));
	} else {
		this->dashCDUI.setScale(sf::Vector2f(game->player->dashCD / game->player->baseCD, 1));

	}
}

void UI::CheckForWinAndLose()
{
	if (game->listEnemy.empty() && game->nbWave >= 7 && game->player->vie > 0) {
		this->texteWinLose.setString("VICTORY");
		this->texteWinLose.setPosition(game->player->posX - 265.0f, game->player->posY);

	} else if (game->player->typeMovement == ACTION::DEAD)
	{
		this->texteWinLose.setString("YOU DIED");
		this->texteWinLose.setPosition(game->player->posX - 288.0f, game->player->posY);
	} else
	{
		this->texteWinLose.setString("");
	}
}

void UI::CheckForNextWave()
{
	if (this->game->timeBeforeCallNewWave > 0.0f)
	{
		float timeNormalized = (int)(this->game->timeBeforeCallNewWave * 10) / 10.0f;
		this->textNextWave.setString(sf::String("Next wave : "));
		this->textNextWave.setPosition(game->player->posX - 850.0f, game->player->posY + 400.0f);
		this->textNextWaveCountdown.setString(to_string(timeNormalized).substr(0, 3));
		this->textNextWaveCountdown.setPosition(game->player->posX - 670.0f, game->player->posY + 400.0f);


	} else
	{
		this->textNextWave.setString(sf::String("Wave "));
		this->textNextWave.setPosition(sf::Vector2f(this->game->player->posX - this->window->getSize().x / 2 + 120.0f, this->game->player->posY + this->window->getSize().y / 2 - 140));
		this->textNextWaveCountdown.setString(to_string(this->game->nbWave));
		this->textNextWaveCountdown.setPosition(sf::Vector2f(this->game->player->posX - this->window->getSize().x / 2 + 220.0f, this->game->player->posY + this->window->getSize().y / 2 - 140));
	}
}

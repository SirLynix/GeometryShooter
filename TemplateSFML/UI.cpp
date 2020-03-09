#include "UI.h"
#include "Game.h"
UI::UI(sf::RenderWindow* window, sf::String fontForText, Game* game) : window(window), game(game)
{
	this->fontForText = new sf::Font;
	this->fontForText->loadFromFile(fontForText);
	this->texteWinLose.setFont(*this->fontForText);

	this->UIRectangle = new sf::RectangleShape;
	this->vie = new sf::Text;
	this->vie->setFont(*this->fontForText);
	this->selectedWeapon = new sf::Text;
	this->selectedWeapon->setFont(*this->fontForText);
	this->ammo = new sf::Text;
	this->ammo->setFont(*this->fontForText);
}

void UI::DisplayUI()
{
	this->window->draw(*this->UIRectangle);
	this->window->draw(*this->vie);

	this->ammo->setString(to_string(game->player->weapon->ammo));
	this->window->draw(*this->ammo);
	this->window->draw(*this->selectedWeapon);
	this->UpdateHpPlayerUI();

	std::list<sf::CircleShape*>::iterator it2 = this->listVies.begin();

	while (it2 != this->listVies.end())
	{
		this->window->draw(*(*it2));
		it2++;
	}

	CheckForWinAndLose();
	this->window->draw(this->texteWinLose);
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
		newCircle->setFillColor(sf::Color::Red);
		newCircle->setOrigin(sf::Vector2f(0.0f, 0.0f));
		this->listVies.push_back(newCircle);
		differenceNbVies--;
	}
}

void UI::UpdatePosUI()
{
	this->UIRectangle->setSize(sf::Vector2f(550.0f, 100.0f));
	this->UIRectangle->setOrigin(sf::Vector2f(0.0f, 0.0f));
	this->UIRectangle->setPosition(sf::Vector2f(this->game->player->posX - 860.0f, this->game->player->posY - 440.0f));
	this->UIRectangle->setFillColor(sf::Color(0, 0, 0, 120));
	this->UIRectangle->setOutlineColor(sf::Color::White);
	this->UIRectangle->setOutlineThickness(2);

	this->vie->setString(sf::String("Vie : "));
	this->vie->setCharacterSize(25);
	this->vie->setPosition(sf::Vector2f(this->UIRectangle->getPosition().x + 20.0f, this->UIRectangle->getPosition().y + 50.0f));
	this->UIRectangle->setOrigin(sf::Vector2f(0.0f, 0.0f));

	this->selectedWeapon->setString(this->game->player->weapon->name.getString());
	this->selectedWeapon->setCharacterSize(25);
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
}

void UI::CheckForWinAndLose()
{
	if (game->listEnemy.empty() && game->nbWave >= 6 && game->player->vie > 0) {
		this->texteWinLose.setString("VICTORY");
		this->texteWinLose.setCharacterSize(100);
		this->texteWinLose.setOrigin(220, 70);
		this->texteWinLose.setPosition(game->player->posX, game->player->posY);
		this->texteWinLose.setFillColor(sf::Color::Red);
	} else if (game->player->typeMovement == ACTION::DEAD)
	{

		this->texteWinLose.setString("YOU DIED");
		this->texteWinLose.setCharacterSize(100);
		this->texteWinLose.setOrigin(220, 70);
		this->texteWinLose.setPosition(game->player->posX, game->player->posY);
		this->texteWinLose.setFillColor(sf::Color::Red);
	} else
	{
		this->texteWinLose.setString("");
	}
}

#include "ShakeScreen.h"

ShakeScreen::ShakeScreen(sf::View* _viewOfGame, sf::Vector2f _originePLayer) : viewOfGame(_viewOfGame), originePLayer(_originePLayer)
{
	shakeSreen = false;
	timeShake = 0.0f;
	coolDownShake = timeShake;
	amplitude = 2.0f;
}

void ShakeScreen::UpdateOrigine(sf::Vector2f _originePLayer)
{
	this->originePLayer = _originePLayer;
}

void ShakeScreen::CheckForShake()
{
	if (shakeSreen && coolDownShake > 0) {
		this->Shake();
	}
	else {
		shakeSreen = false;
		coolDownShake = timeShake;
		viewOfGame->setCenter(originePLayer);
	}
}

void ShakeScreen::UpdateAmplitude(float amplitude)
{
	this->amplitude = amplitude;
}

void ShakeScreen::UpdateTimeShake(float timeShake)
{
	this->timeShake = timeShake;
	this->coolDownShake = timeShake;
}

void ShakeScreen::Shake()
{
	int randome = rand() % 4;

	if (randome == 0) {
		viewOfGame->setCenter(sf::Vector2f(originePLayer.x + amplitude, originePLayer.y));
	}
	else if (randome == 1) {
		viewOfGame->setCenter(sf::Vector2f(originePLayer.x - amplitude, originePLayer.y));
	}
	else if (randome == 2) {
		viewOfGame->setCenter(sf::Vector2f(originePLayer.x, originePLayer.y + amplitude));
	}
	else if (randome == 3) {
		viewOfGame->setCenter(sf::Vector2f(originePLayer.x - amplitude, originePLayer.y - amplitude));
	}

}

void ShakeScreen::UpdateCooldown(float deltaTime)
{
	this->coolDownShake -= deltaTime;
}

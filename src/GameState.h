#pragma once
#include <SFML/Graphics.hpp>

class GameState
{
public:

	GameState(sf::RenderWindow* fenetre) : fenetre_(fenetre) {};
	virtual int run() = 0;

protected:
	sf::RenderWindow* fenetre_;
};

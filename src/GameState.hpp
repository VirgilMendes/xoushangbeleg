#pragma once
#include <SFML/Graphics.hpp>

class GameState
{
public:

	GameState(sf::RenderWindow* window) : window_(window) {};
	virtual void run() = 0;

protected:
	sf::RenderWindow* window_;
};

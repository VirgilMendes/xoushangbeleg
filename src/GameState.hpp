#pragma once
#include <SFML/Window/Event.hpp>

class GameState
{
	GameState() = default;
	
	virtual void run(sf::Event* event) = 0;
};

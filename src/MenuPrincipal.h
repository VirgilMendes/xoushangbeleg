#ifndef DEF_MENUPRINCIPAL
#define DEF_MENUPRINCIPAL
#include "GameState.hpp"
#pragma once


#include <string>

class MenuPrincipal : GameState 
{
public:

	MenuPrincipal(sf::RenderWindow* fenetre);
	int run () override;
	

private:
	int choix;

	int frame;

	sf::Texture titre;
	sf::Sprite sprite;
	sf::IntRect animation[11];

	sf::Font font;
	sf::Text TabMenu[4];

	bool toucheLache;
};

#endif
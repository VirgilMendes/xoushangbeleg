#ifndef DEF_MENUPRINCIPAL
#define DEF_MENUPRINCIPAL
#pragma once


#include <string>

class MenuPrincipal
{
public:

	MenuPrincipal();
	int RunMenuPrincipal();
	

private:
	int choix;

	sf::RenderWindow fenetre;
	int frame;

	sf::Sprite sprite;
	sf::IntRect animation[11];

	sf::Font font;
	sf::Text TabMenu[4];

	bool toucheLache;
};

#endif
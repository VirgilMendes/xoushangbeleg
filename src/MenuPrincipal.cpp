#include "SFML\Graphics.hpp"
#include "SFML\Config.hpp"

#include "MenuPrincipal.h"

class MenuPrincipal {

	sf::Window fenetre;

	MenuPrincipal::MenuPrincipal()
	{
		fenetre.create(sf::VideoMode(800, 600), "My window");
	}

	int MenuPrincipal::choix()
	{

	}
};
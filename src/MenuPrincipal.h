#ifndef DEF_MENUPRINCIPAL
#define DEF_MENUPRINCIPAL

#include "SFML\Graphics.hpp"
#include "SFML\Config.hpp"


class MenuPrincipal
{
public:

	MenuPrincipal();
	int choix();

private:

	sf::Window fenetre;

};

#endif
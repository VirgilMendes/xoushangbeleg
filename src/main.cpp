#include "VueCombat.h"
#include "MenuPrincipal.h"
#include "NouvellePartie.h"
#include <thread>

int main()
	{
		sf::RenderWindow fenetre(sf::VideoMode(1000, 700), "Xoushangbeleg");
		fenetre.setFramerateLimit(60);
		VueCombat vueCombat(&fenetre);
		vueCombat.ajouterUnite("Archer2","ressources/sprite/Archer_sprite.png", sf::Vector2i(1, 1));
		vueCombat.ajouterUnite("Tank","ressources/sprite/Tank_sprite.png", sf::Vector2i(1, 2));
		vueCombat.ajouterUnite("Soldat","ressources/sprite/Soldat_sprite.png", sf::Vector2i(2, 1));
		while (fenetre.isOpen())
		{
			vueCombat.run();
		}
		fenetre.create(sf::VideoMode(1000, 700), "Xoushangbeleg");
		MenuPrincipal menuPrincipal(&fenetre);
		while (fenetre.isOpen())
		{
			if (menuPrincipal.run() == 4) fenetre.close();
		}

		fenetre.create(sf::VideoMode(1000, 700), "Xoushangbeleg");
		NouvellePartie nouvellePartie(&fenetre);
		nouvellePartie.setIP();
		while (fenetre.isOpen())
		{
			if (nouvellePartie.run() == 3) fenetre.close();
		}

		
	}

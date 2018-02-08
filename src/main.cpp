#include "VueCombat.hpp"
#include "MenuPrincipal.h"
#include "NouvellePartie.hpp"
#include <thread>

int main()
	{
		sf::RenderWindow fenetre(sf::VideoMode(1000, 700), "Xoushangbeleg");
		fenetre.setFramerateLimit(60);
		VueCombat vueCombat(&fenetre);
		//vueCombat.ajouterUnite(sf::Vector2i(1, 1));
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
		while (fenetre.isOpen())
		{
			if (nouvellePartie.run() == 3) fenetre.close();
		}

		
	}

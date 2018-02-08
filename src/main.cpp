#include "VueCombat.hpp"
#include "MenuPrincipal.h"
#include "NouvellePartie.cpp"
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

		std::thread nouvellePartie(NouvellePartieRun);
		nouvellePartie.join();

		
	}

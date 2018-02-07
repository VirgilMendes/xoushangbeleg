#include "VueCombat.hpp"
#include "MenuPrincipal.h"
#include "NouvellePartie.cpp"
#include <thread>

int main()
	{
		sf::RenderWindow fenetre(sf::VideoMode(1000, 700), "Xoushangbeleg");
		fenetre.setFramerateLimit(60);
		VueCombat vueCombat(&fenetre);
		while (fenetre.isOpen())
		{
			vueCombat.run();
		}
		fenetre.setFramerateLimit(60);
		MenuPrincipal menuPrincipal();
		std::thread nouvellePartie(NouvellePartieRun);
		nouvellePartie.join();
	}

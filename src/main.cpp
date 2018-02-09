#include "VueCombat.h"
#include "MenuPrincipal.h"
#include "NouvellePartie.h"
#include <thread>

int main()
	{
		sf::RenderWindow fenetre(sf::VideoMode(1000, 700), "Xoushangbeleg");
		fenetre.setFramerateLimit(60);
		VueCombat vueCombat(&fenetre);
		vueCombat.ajouterUnite("Archer2","ressources/sprite/Archer_sprite.png", Vecteur2<int>(1, 1));
		vueCombat.ajouterUnite("Tank","ressources/sprite/Tank_sprite.png", Vecteur2<int>(1, 2));
		vueCombat.ajouterUnite("Soldat","ressources/sprite/Soldat_sprite.png", Vecteur2<int>(2, 1));
		vueCombat.deplacerUnite("Tank", Vecteur2<int>(9, 4));
		while (fenetre.isOpen())
		{
			vueCombat.run();
		}
		fenetre.create(sf::VideoMode(1000, 700), "Xoushangbeleg");
		MenuPrincipal menuPrincipal(&fenetre);
		menuPrincipal.setFichiers(true);
		while (fenetre.isOpen())
		{
			if (menuPrincipal.run() == 4) fenetre.close();
			
		}

		fenetre.create(sf::VideoMode(1000, 700), "Xoushangbeleg");
		NouvellePartie nouvellePartie(&fenetre);
		nouvellePartie.setIP("192.555.12.22");
		while (fenetre.isOpen())
		{
			if (nouvellePartie.run() == 3) fenetre.close();
		}

		
	}

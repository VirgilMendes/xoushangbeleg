#include "Vue/VueCombat.h"
#include "Vue/MenuPrincipal.h"
#include "Vue/NouvellePartie.h"
#include <thread>

int main()
	{
		sf::RenderWindow fenetre(sf::VideoMode(1000, 700), "Xoushangbeleg");
		fenetre.setFramerateLimit(60);
		/*Vue::VueCombat vueCombat(&fenetre);
		vueCombat.ajouterUnite("Archer2","ressources/sprite/Archer_sprite.png", Modele::Vecteur2<int>(1, 1));
		vueCombat.ajouterUnite("Tank","ressources/sprite/Tank_sprite.png", Modele::Vecteur2<int>(1, 2));
		vueCombat.ajouterUnite("Soldat","ressources/sprite/Soldat_sprite.png", Modele::Vecteur2<int>(2, 1));
		vueCombat.deplacerUnite("Tank", Modele::Vecteur2<int>(9, 4));
		while (fenetre.isOpen())
		{
			vueCombat.run();
		}*/
		fenetre.create(sf::VideoMode(1000, 700), "Xoushangbeleg");
		Vue::MenuPrincipal menuPrincipal(&fenetre);
		menuPrincipal.setFichiers(true);
		while (fenetre.isOpen())
		{
			if (menuPrincipal.run() == 4) fenetre.close();
			
		}

		fenetre.create(sf::VideoMode(1000, 700), "Xoushangbeleg");
		Vue::NouvellePartie nouvellePartie(&fenetre);
		nouvellePartie.setIP("192.555.12.22");
		while (fenetre.isOpen())
		{
			if (nouvellePartie.run() == 3) fenetre.close();
		}

		
	}

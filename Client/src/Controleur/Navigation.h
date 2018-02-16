#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Vue/GameState.h"
#include <stack>
#include "../Vue/VueCombat.h"

namespace Controleur
{
	class Fenetre : public sf::RenderWindow
	{
	public:
		Fenetre() : RenderWindow(sf::VideoMode(1000, 700), "Xoushangbeleg")
		{
			setFramerateLimit(60);
			gameStates_.push(new Vue::VueCombat(this));
			Vue::VueCombat* vueCombat = dynamic_cast<Vue::VueCombat*>(gameStates_.top());
			vueCombat->ajouterUnite("Archer2","ressources/sprite/Archer_sprite.png", Modele::Vecteur2<int>(1, 1));
			vueCombat->ajouterUnite("Tank","ressources/sprite/Tank_sprite.png", Modele::Vecteur2<int>(1, 2));
			vueCombat->ajouterUnite("Soldat","ressources/sprite/Soldat_sprite.png", Modele::Vecteur2<int>(2, 1));
			vueCombat->deplacerUnite("Tank", Modele::Vecteur2<int>(9, 4));
		}

		void run()
		{
			while (isOpen())
			{
				gameStates_.top()->run();
			}
		}

	private:

		std::stack<Vue::GameState*> gameStates_;
	};
}

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Vue/GameStates/GameState.h"
#include <stack>
#include "../Vue/GameStates/VueCombat.h"

namespace Controleur
{
	class Fenetre : public sf::RenderWindow
	{
	public:
		Fenetre() : RenderWindow(sf::VideoMode(1000, 700), "Xoushangbeleg")
		{
			setFramerateLimit(60);
			Vue::VueCombat* vueCombat = new Vue::VueCombat(this);
			gameStates_.push(vueCombat);
			vueCombat->deplacerUnite("Archer1", sf::Vector2i(10, 7));
		}

		void run()
		{
			while (isOpen())
			{
				gameStates_.top()->run();
			}
		}

		void ajouterGameState(Vue::GameState* gamestate)
		{
			gameStates_.push(gamestate);
		}

	private:

		std::stack<Vue::GameState*> gameStates_;
	};
}

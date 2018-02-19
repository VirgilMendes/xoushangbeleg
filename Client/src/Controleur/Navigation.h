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
			gameStates_.push(new Vue::MenuPrincipal(this));
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

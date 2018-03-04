#pragma once

#include "Navigation.h"

namespace Controleur
{

	sf::RenderWindow* Fenetre::fenetre = nullptr;
	std::stack<Vue::GameState*> Fenetre::gameStates_;

	void Fenetre::initialiser()
	{
		fenetre = new sf::RenderWindow(sf::VideoMode(1000, 700), "Xoushangbeleg");
		fenetre->setFramerateLimit(60);
		Vue::Combat* combat = new Vue::Combat();
		gameStates_.push(combat);
	}

	void Fenetre::run()
	{
		while (fenetre->isOpen())
		{
			if (gameStates_.empty())
			{
				fenetre->close();
				break;
			}

			sf::Event event;
			while (fenetre->pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					fenetre->close();
					break;
				default:
					gameStates_.top()->handleEvent(event);
				}
			}
				gameStates_.top()->update();

				fenetre->clear(sf::Color::Black);
				gameStates_.top()->draw();
				fenetre->display();
			
		}
	}

	void Fenetre::empilerGameState(Vue::GameState* gamestate)
	{
		gameStates_.push(gamestate);
	}

	void Fenetre::depilerGameState()
	{
		delete gameStates_.top();
		gameStates_.pop();
	}
}

#pragma once

#include "Navigation.h"

namespace Controleur
{

	sf::RenderWindow* Fenetre::fenetre = nullptr;
	std::list<Vue::GameState*> Fenetre::gameStates_;

	void Fenetre::initialiser()
	{
		fenetre = new sf::RenderWindow(sf::VideoMode(1000, 700), "Xoushangbeleg");
		fenetre->setFramerateLimit(60);
		Vue::Combat* combat = new Vue::Combat();
		gameStates_.push_back(combat);
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
					gameStates_.back()->handleEvent(event);
				}
			}
			
			std::list<Vue::GameState*>::reverse_iterator iterateur(gameStates_.rbegin());

			fenetre->clear(sf::Color::Black);

			while ((*iterateur)->estInterfaceUtilisateur() && iterateur != gameStates_.rend())
				++iterateur;
			while(iterateur != gameStates_.rbegin())
			{
				(*iterateur)->update();
				(*iterateur)->draw();
				--iterateur;
			}
			(*iterateur)->update();
			(*iterateur)->draw();

			fenetre->display();
			
		}
	}

	void Fenetre::empilerGameState(Vue::GameState* gamestate)
	{
		gameStates_.push_back(gamestate);
	}

	void Fenetre::depilerGameState()
	{
		delete gameStates_.back();
		gameStates_.back();
	}
}

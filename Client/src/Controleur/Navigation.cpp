#pragma once

#include "Navigation.h"
#include "GameStates/MenuChoix.h"

namespace Controleur
{

	sf::RenderWindow* Fenetre::fenetre = nullptr;
	std::list<GameState*> Fenetre::gameStates_;

	void Fenetre::initialiser()
	{
		fenetre = new sf::RenderWindow(sf::VideoMode(1000, 700), "Xoushangbeleg");
		fenetre->setFramerateLimit(60);
		Grille* grille = new Grille(Modele::Vecteur2<int>(32,32));
		gameStates_.push_front(grille);
		MenuChoix* menuAction = new MenuChoix(std::vector<Choix>
		{ 
			{ "choix actif", false , []{}}, 
			{ "choix actif", true }, 
			{ "choix inactif", true },
			{ "choix inactif", true },
			{ "choix actif", false },
			{ "choix inactif", true },
		});
		gameStates_.push_front(menuAction);
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
			
			gameStates_.front()->handleEvent();

			std::list<GameState*>::iterator iterateur(gameStates_.begin());

			fenetre->clear(sf::Color::Black);

			while ((*iterateur)->estInterfaceUtilisateur() && iterateur != gameStates_.end())
				++iterateur;
			while(iterateur != gameStates_.begin())
			{
				(*iterateur)->update();
				(*iterateur)->afficher();
				--iterateur;
			}
			(*iterateur)->update();
			(*iterateur)->afficher();

			fenetre->display();
			
		}
	}

	void Fenetre::empilerGameState(GameState* gamestate)
	{
		gameStates_.push_front(gamestate);
	}

	void Fenetre::depilerGameState()
	{
		delete gameStates_.front();
		gameStates_.front();
	}
}


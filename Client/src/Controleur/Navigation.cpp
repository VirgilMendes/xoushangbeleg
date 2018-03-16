#pragma once

#include "Navigation.h"
#include "GameStates/MenuChoix.h"
#include  "GameStates/Grille.h"
#include "GameStates/Menu/MenuPrincipal.h"

namespace Controleur
{

	sf::RenderWindow* Fenetre::fenetre = nullptr;
	sf::Font Fenetre::policeParDefaut_;
	std::list<GameState*> Fenetre::gameStates_;
	std::list<GameState*> Fenetre::cache_;

	void Fenetre::initialiser()
	{
		fenetre = new sf::RenderWindow(sf::VideoMode(1280, 720), "Xoushangbeleg");
		fenetre->setFramerateLimit(60);
		if (!policeParDefaut_.loadFromFile("ressources/VCR_OSD_MONO_1.001.ttf"))
		{
			std::cout << "Impossible d'ouvrir la police par défaut" << std::endl;
		}
		MenuPrincipal* menu = new MenuPrincipal();
		gameStates_.push_front(menu);
	}

	void Fenetre::run()
	{
		while (!cache_.empty())
		{
			delete cache_.back();
			cache_.pop_back();
		}
		
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
		cache_.push_back(gameStates_.front());
		gameStates_.pop_front();
	}

	Grille* Fenetre::getProchaineGrille()
	{
		auto iterateur = gameStates_.begin();
		while (dynamic_cast<Grille*>(*iterateur) == nullptr)
		{
			++iterateur;
			if (iterateur == gameStates_.end())
			{
				return nullptr;
			}
		}
		return dynamic_cast<Grille*>(*iterateur);
	}

	sf::Font& Fenetre::getPoliceParDefaut()
	{
		return policeParDefaut_;
	}
}


#pragma once

#include "../../Controleur/Navigation.h"
#include "Combat.h"


namespace Vue
{
	Combat::Combat() : grille_(new Modele::Grille(Modele::Vecteur2<int>(32,32)))
	{
		grille_.ajouterUnite("Archer1", "ressources/sprite/Archer_sprite.png", sf::Vector2i(4, 3));

		sf::Font font;
		font.loadFromFile("ressources/VCR_OSD_MONO_1.001.ttf");
		menuAction_ = new MenuChoix(std::vector<std::string>{"test1", "test2", "test3"}, font, 20);
		menuAction_->setPosition(Modele::Vecteur2<int>(600, 0));
	}

	Combat::~Combat()
	{
		delete menuAction_;
	}

	void Combat::handleEvent(sf::Event event)
	{
		switch (event.type)
		{

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Z: case sf::Keyboard::Up:
				grille_.deplacerCurseur(Modele::Vecteur2<int>(0,-1));
				menuAction_->deplacerAuChoixPrecedant();
				break;
			case sf::Keyboard::Q: case sf::Keyboard::Left:
				grille_.deplacerCurseur(Modele::Vecteur2<int>(-1, 0));
				break;
			case sf::Keyboard::S: case sf::Keyboard::Down:
				grille_.deplacerCurseur(Modele::Vecteur2<int>(0, 1));
				menuAction_->deplacerAuChoixSuivant();
				break;
			case sf::Keyboard::D: case sf::Keyboard::Right:
				grille_.deplacerCurseur(Modele::Vecteur2<int>(1, 0));
				break;
			case sf::Keyboard::K: case sf::Keyboard::Return:
				grille_.afficherCaseAccessible();
			default: break;
			}
		}
	}

	void Combat::update()
	{
		
	}

	void Combat::draw()
	{
		grille_.dessiner(*Controleur::Fenetre::fenetre, sf::Transform());
		
	

		menuAction_->dessiner(Controleur::Fenetre::fenetre, sf::Transform());
	}
	
}

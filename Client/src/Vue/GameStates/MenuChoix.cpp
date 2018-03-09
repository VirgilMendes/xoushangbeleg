#pragma once

#include "MenuChoix.h"
#include "../../Controleur/Navigation.h"
#include "../../Controleur/GameStates/MenuChoix.h"

namespace Vue
{
	MenuChoix::MenuChoix(std::vector<Controleur::Choix> choix, Controleur::MenuChoix* controleur): controleur_(controleur), choixCourant_(0)
	{
		tailletexte_ = 20;
		police_.loadFromFile("ressources/VCR_OSD_MONO_1.001.ttf");
		for (int i(0); i < choix.size(); i++)
			{
				const std::string texteChoix = choix[i].texte;
				sf::Text* texte = new sf::Text(texteChoix, police_, tailletexte_);
				texte->setFillColor(couleurActif_);
				texte->move(5, tailletexte_ * i);
				textes_.push_back(texte);
			}
	}

	MenuChoix::~MenuChoix()
	{
		for (sf::Text* texte : textes_)
			delete texte;
	}

	void MenuChoix::setChoixCourant(int index)
	{
		choixCourant_ = index;
		textes_[index]->setFillColor(couleurSelection_);
	}
	
	void MenuChoix::changerChoixCourant(int index)
	{
		textes_[choixCourant_]->setFillColor(couleurActif_);
		choixCourant_ = index;
		textes_[index]->setFillColor(couleurSelection_);
	}

	void MenuChoix::activerChoix(int index)
	{
		textes_[index]->setFillColor(couleurActif_);
	}

	void MenuChoix::desactiverChoix(int index)
	{
		textes_[index]->setFillColor(couleurInactif_);
	}

	void MenuChoix::handleEvent()
	{
		sf::Event event;
		while (Controleur::Fenetre::fenetre->pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::Closed:
				Controleur::Fenetre::fenetre->close();
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Z: case sf::Keyboard::Up:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Haut);
					break;
				case sf::Keyboard::D: case sf::Keyboard::Right:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Droite);
					break;
				case sf::Keyboard::S: case sf::Keyboard::Down:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Bas);
					break;
				case sf::Keyboard::Q: case sf::Keyboard::Left:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Gauche);
					break;
				case sf::Keyboard::K: case sf::Keyboard::Return:
					controleur_->enclencherActionValidation();
				case sf::Keyboard::Escape:
					Controleur::Fenetre::fenetre->close();
				default: break;
				}
			}
		}
	}

	void MenuChoix::update()
	{
	}

	void MenuChoix::afficher()
	{
		sf::RenderWindow* cible= Controleur::Fenetre::fenetre;
		for (sf::Text* texte : textes_)
		{
			cible->draw(*texte);
		}
	}
}

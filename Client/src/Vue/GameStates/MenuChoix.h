#pragma once
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "GameState.h"
#include "../Outils/Node.h"
#include <iostream>

namespace Controleur
{
	class MenuChoix;
	class Choix;
}

namespace Vue
{

	class MenuChoix : public GameState
	{
	public:

		MenuChoix(std::vector<Controleur::Choix> choix, Controleur::MenuChoix* controleur);
		~MenuChoix();

		void changerChoixCourant(int index);
		void setChoixCourant(int index);

		void activerChoix(int index);
		void desactiverChoix(int index);

		void handleEvent() override;
		void update() override;
		void afficher() override;
	
	protected:

		//Gestion des textes
		sf::Font police_;
		int tailletexte_;
		std::vector<sf::Text*> textes_;
		int choixCourant_;

		//Gestion des couleurs
		sf::Color couleurSelection_ = sf::Color::Yellow;
		sf::Color couleurInactif_ = sf::Color(100, 100, 100);
		sf::Color couleurActif_ = sf::Color::White;

		Controleur::MenuChoix* controleur_;
	};
}

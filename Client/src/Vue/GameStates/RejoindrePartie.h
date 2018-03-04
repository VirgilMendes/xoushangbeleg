#pragma once

#include "GameState.h"
#include <string>
#include "../Outils/Animation.h"


namespace Vue
{

	class RejoindrePartie : public GameState
	{
	public:

		RejoindrePartie(Controleur::Fenetre* fenetre);
		void handleEvent(sf::Event event) override;
		void update() override;
		void draw() override;
		std::string RejoindrePartie::getIP();



	private:
		
		int choix_;

		bool ipRemplie_;
		
		sf::Color gris = sf::Color(100, 100, 100);
		
		std::string str;

		sf::Texture textureLogo_;
		sf::Sprite logo_;
		Animation animationtitre_;

		sf::Text menu_[3];
		sf::Font font_;

		sf::Text titreMenu_;
		sf::Text ip_;
		std::string ipPartie_;


		bool toucheLache_;
	};

}


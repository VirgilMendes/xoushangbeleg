#pragma once

#include <string>
#include "../Outils/Animation.h"
#include "../GameStates/GameState.h"

namespace Vue
{

	class NouvellePartie : public GameState
	{
	public:

		NouvellePartie();
		void handleEvent() override;
		void update() override;
		void afficher() override;

		void NouvellePartie::setIP();
		void NouvellePartie::setIP(std::string std);
		std::string NouvellePartie::getIP();



	private:
		int choix_;

		sf::Texture textureLogo_;
		sf::Sprite logo_;
		Animation animationtitre_;

		sf::Text menu_[3];
		sf::Font font_;

		sf::Text titreMenu_;
		sf::Text ip_;
		std::string nomPartie_;


		bool toucheLache_;
	};

}

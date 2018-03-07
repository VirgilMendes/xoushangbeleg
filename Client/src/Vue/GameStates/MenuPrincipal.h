#pragma once

#include "../Outils/Jauge.h"
#include <string>
#include "../Outils/Animation.h"
#include "../GameStates/GameState.h"

namespace Vue
{

	class MenuPrincipal : public GameState
	{
	public:

		MenuPrincipal();
		void handleEvent() override;
		void update() override;
		void dessiner() override;
		void setFichiers(bool filesExistant);

	private:
		int choix_;

		bool sauvegardeExistante_;

		sf::Color gris_ = sf::Color(100, 100, 100);

		sf::Texture textureTitre_;
		sf::Sprite titre_;

		Animation animationtitre_;

		sf::Font font_;
		sf::Text TabMenu_[4];

		bool toucheLache_;
	};

}

#ifndef DEF_MENUPRINCIPAL
#define DEF_MENUPRINCIPAL
#include "GameState.h"
#include "Jauge.h"
#pragma once


#include <string>
#include "Animation.h"

namespace Vue
{

	class MenuPrincipal : public GameState
	{
	public:

		MenuPrincipal(sf::RenderWindow* fenetre);
		int run() override;
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
#endif
#ifndef DEF_MENUPRINCIPAL
#define DEF_MENUPRINCIPAL
#include "GameState.h"
#include "Jauge.h"
#pragma once


#include <string>

namespace Vue
{

	class MenuPrincipal : GameState
	{
	public:

		MenuPrincipal(sf::RenderWindow* fenetre);
		int run() override;
		void setFichiers(bool filesExistant);

	private:
		int choix;

		bool fichiers;

		int frame;

		sf::Color gris = sf::Color(100, 100, 100);

		sf::Texture titre;
		sf::Sprite sprite;
		sf::IntRect animation[11];

		Jauge J;


		sf::Font font;
		sf::Text TabMenu[4];

		bool toucheLache;
	};

}
#endif
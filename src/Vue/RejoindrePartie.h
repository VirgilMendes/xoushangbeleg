#ifndef DEF_REJOINDREPARTIE
#define DEF_REJOINDREPARTIE
#include "GameState.h"
#include <string>
#pragma once

namespace Vue
{

	class RejoindrePartie : GameState
	{
	public:

		RejoindrePartie(sf::RenderWindow* fenetre);
		int run() override;
		std::string RejoindrePartie::getIP();



	private:
		int choix;

		int frame;

		sf::Texture titre;
		sf::Sprite sprite;
		sf::IntRect animation[11];
		std::string str;
		sf::Text titreCrea;
		sf::Text numIP;
		std::string chaineNom;
		sf::Font font;
		sf::Text TabMenu[3];

		bool toucheLache;
	};

}
#endif

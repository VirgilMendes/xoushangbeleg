#ifndef DEF_NOUVELLEPARTIE
#define DEF_NOUVELLEPARTIE
#include "GameState.hpp"
#include <string>
#pragma once


class NouvellePartie : GameState
{
public:

	NouvellePartie(sf::RenderWindow* fenetre);
	int run() override;
	void NouvellePartie::setIP();


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
#endif

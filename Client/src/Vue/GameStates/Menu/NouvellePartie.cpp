#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "NouvellePartie.h"
#include "../../../Controleur/Navigation.h"
#include "../../../Controleur/GameStates/MenuChoix.h"
#include "../../../Controleur/GameStates/Menu/NouvellePartie.h"

namespace Vue
{

	NouvellePartie::NouvellePartie(std::vector<Controleur::Choix> choix, Controleur::NouvellePartie* controleur): MenuChoix(choix, controleur)
	{
		if (!textureLogo_.loadFromFile("ressources/sprite/titre.png"))
		{
			std::cout << "error img titre" << std::endl;
		}
		textureLogo_.setSmooth(false);
		logo_.setTexture(textureLogo_);

		std::vector<sf::IntRect> animation
		{
			sf::IntRect(0, 0, 512, 256),
			sf::IntRect(0, 256, 512, 256),
			sf::IntRect(0, 256 * 2, 512, 256),
			sf::IntRect(0, 256 * 3, 512, 256),
			sf::IntRect(0, 256 * 4, 512, 256),
			sf::IntRect(0, 256 * 5, 512, 256),
			sf::IntRect(0, 256 * 6, 512, 256),
			sf::IntRect(0, 256 * 7, 512, 256),
			sf::IntRect(0, 256 * 8, 512, 256),
			sf::IntRect(0, 256 * 9, 512, 256),
			sf::IntRect(0, 256 * 10, 512, 256)
		};
		animationLogo_.initialiser(animation, 100);

		logo_.setPosition(500, 100);

		for (int i(0); i < textes_.size(); ++i)
		{
			textes_[i]->setPosition(600, i * 50 + 400);
		}

		titreMenu_.setString("Creer Une Partie");
		titreMenu_.setFont(Controleur::Fenetre::getPoliceParDefaut());
		titreMenu_.setCharacterSize(36);
		titreMenu_.setFillColor(sf::Color::White);
		titreMenu_.setPosition(500, 325);

		ip_.setString("IP : ");
		ip_.setFont(Controleur::Fenetre::getPoliceParDefaut());
		ip_.setCharacterSize(24);
		ip_.setFillColor(sf::Color::White);
		ip_.setPosition(30, 650);

	}



	void NouvellePartie::afficher()
	{
		MenuChoix::afficher();
		logo_.setTextureRect(animationLogo_.getFrame());
		Controleur::Fenetre::fenetre->draw(logo_);
		Controleur::Fenetre::fenetre->draw(ip_);
		Controleur::Fenetre::fenetre->draw(titreMenu_);
		
	}


	void NouvellePartie::setIP(std::string str) {
		ip_.setString(str);
	}

	std::string NouvellePartie::getIP() {
		return ip_.getString();

	}

}
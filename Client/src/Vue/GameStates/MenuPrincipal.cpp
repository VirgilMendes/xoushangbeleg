#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "MenuPrincipal.h"
#include "../Outils/Jauge.h"
#include "../../Controleur/Navigation.h"

namespace Vue
{

	MenuPrincipal::MenuPrincipal(std::vector<Controleur::Choix> choix, Controleur::MenuPrincipal* controleur) : MenuChoix(choix, controleur)
	{

		if (!textureTitre_.loadFromFile("ressources/sprite/titre.png"))
		{
			std::cout << "impossible d'ouvrir l'image du titre" << std::endl;
		}
		textureTitre_.setSmooth(false);

		titre_.setTexture(textureTitre_);

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
		animationtitre_.initialiser(animation, 100);

		titre_.setPosition(500, 100);
		for (int i(0); i < textes_.size(); ++i)
		{
			textes_[i]->setPosition(600, i * 50 + 400);
		}
	}

	void MenuPrincipal::afficher()
	{
		MenuChoix::afficher();
		titre_.setTextureRect(animationtitre_.getFrame());
		Controleur::Fenetre::fenetre->draw(titre_);
	}
}




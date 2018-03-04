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
	
	MenuPrincipal::MenuPrincipal() : choix_(0), toucheLache_(true), sauvegardeExistante_(false)
	{	

		if (!textureTitre_.loadFromFile("ressources/sprite/titre.png"))
		{
			std::cout << "impossible d'ouvrir l'image" << std::endl;
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

		titre_.setPosition(300, 100);

		if (!font_.loadFromFile("ressources/VCR_OSD_MONO_1.001.ttf"))
		{
			std::cout << "impossible d'ouvrir la police" << std::endl;
		}

		TabMenu_[0].setString("Nouveau");
		TabMenu_[1].setString("Rejoindre");
		TabMenu_[2].setString("Charger");
		TabMenu_[3].setString("Quitter");

		for (int i = 0; i < 4; i++)
		{
			TabMenu_[i].setFont(font_);
			TabMenu_[i].setCharacterSize(24);
			TabMenu_[i].setFillColor(sf::Color::White);
			TabMenu_[i].setPosition(450, i * 50 + 400);
		}
	}

	void MenuPrincipal::setFichiers(bool sauvegardeExistante)
	{
		sauvegardeExistante_ = sauvegardeExistante;
	}

	void MenuPrincipal::handleEvent(sf::Event event)
	{

		TabMenu_[choix_].setFillColor(sf::Color::White);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && toucheLache_)
		{
			if (choix_ > 0)
			{
				if (!sauvegardeExistante_ && choix_ == 3)
				{
					choix_ -= 2;
				}
				else
				{
					choix_ -= 1;
				}
			}
			toucheLache_ = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && toucheLache_)
		{
			if (choix_ < 3)
			{
				if (!sauvegardeExistante_ && choix_ == 1)
				{
					choix_ += 2;
				}
				else
				{
					choix_ += 1;
				}
			}
			toucheLache_ = false;
		}

		if (event.type == sf::Event::KeyReleased)
		{
			toucheLache_ = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
		}
	}

	void MenuPrincipal::update()
	{
		if (!sauvegardeExistante_) // charger gris
		{
			TabMenu_[2].setFillColor(gris_);
		}
		else
		{
			TabMenu_[2].setFillColor(sf::Color::White);
		}
		TabMenu_[choix_].setFillColor(sf::Color::Yellow);
	}

	void MenuPrincipal::draw()
	{
		for (int i = 0; i < 4; i++)
		{
			Controleur::Fenetre::fenetre->draw(TabMenu_[i]);
		}

		Controleur::Fenetre::fenetre->draw(titre_);

		titre_.setTextureRect(animationtitre_.getFrame());

	}

}




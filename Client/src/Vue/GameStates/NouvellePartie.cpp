#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "NouvellePartie.h"
#include "../../Controleur/Navigation.h"

namespace Vue
{

	NouvellePartie::NouvellePartie() : choix_(1), toucheLache_(true) {

		nomPartie_ = "Nom de la partie : ";
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
		animationtitre_.initialiser(animation, 100);

		logo_.setPosition(300, 100);

		if (!font_.loadFromFile("ressources/VCR_OSD_MONO_1.001.ttf"))
		{
			std::cout << "error font" << std::endl;
		}

		menu_[0].setString("Creer");
		menu_[1].setString(nomPartie_);
		menu_[2].setString("Retour");
		
		titreMenu_.setString("Nouvelle partie");

		for (int i = 0; i < 3; i++)
		{
			menu_[i].setFont(font_);
			menu_[i].setCharacterSize(24);
			menu_[i].setFillColor(sf::Color::White);
			menu_[i].setPosition(310, i * 50 + 320);
		}

		titreMenu_.setFont(font_);
		titreMenu_.setCharacterSize(36);
		titreMenu_.setFillColor(sf::Color::White);
		titreMenu_.setPosition(350, 230);


		ip_.setFont(font_);
		ip_.setCharacterSize(24);
		ip_.setFillColor(sf::Color::White);
		ip_.setPosition(30, 650);

	}
	void NouvellePartie::handleEvent()
	{

		/*menu_[choix_].setFillColor(sf::Color::White);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && toucheLache_)
		{
			if (choix_ > 0)
			{
				choix_ -= 1;
			}
			toucheLache_ = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && toucheLache_)
		{
			if (choix_ < 2)
			{
				choix_ += 1;
			}
			toucheLache_ = false;
		}

		if (event.type == sf::Event::TextEntered)
		{
			if (choix_ == 1)
			{

				if (event.type == sf::Event::TextEntered && nomPartie_.size() < 30 && !sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					// ASCII seulement
					if (event.text.unicode < 128)
					{
						nomPartie_ += static_cast<char>(event.text.unicode);
						menu_[1].setString(nomPartie_);
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && nomPartie_.size() > 19)
				{
					nomPartie_.erase(nomPartie_.end() - 1);
					menu_[1].setString(nomPartie_);
				}
			}
			else if (choix_ == 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
			}
			toucheLache_ = false;
		}

		if (event.type == sf::Event::KeyReleased)
		{
			toucheLache_ = true;
		}*/
	}

	void NouvellePartie::update()
	{
		menu_[choix_].setFillColor(sf::Color::Yellow);
		logo_.setTextureRect(animationtitre_.getFrame());
	}

	void NouvellePartie::afficher()
	{
		Controleur::Fenetre::fenetre->draw(ip_);
		Controleur::Fenetre::fenetre->draw(titreMenu_);

		menu_[choix_].setFillColor(sf::Color::Yellow);

		for (int i(0); i < 3; i++)
		{
			Controleur::Fenetre::fenetre->draw(menu_[i]);
		}

		Controleur::Fenetre::fenetre->draw(logo_);

	}


	void NouvellePartie::setIP(std::string str) {
		ip_.setString(str);
	}

	std::string NouvellePartie::getIP() {
		return ip_.getString();

	}

}
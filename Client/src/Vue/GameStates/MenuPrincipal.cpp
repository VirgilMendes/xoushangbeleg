#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "MenuPrincipal.h"
#include "../Outils/Jauge.h"

namespace Vue
{
	
	MenuPrincipal::MenuPrincipal(sf::RenderWindow* fenetre) : GameState(fenetre), choix_(0), toucheLache_(true), sauvegardeExistante_(false)
	{	
		//Titre est une texture donc il a un constructeur par défaut et n'a pas besoin d'être initialisé

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

		// GESTION DE L'ECRITURE

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
			TabMenu_[i].setFont(font_);// choix de la police à utiliser
			TabMenu_[i].setCharacterSize(24);// choix de la taille des caractères
			TabMenu_[i].setFillColor(sf::Color::White);
			TabMenu_[i].setPosition(450, i * 50 + 400);
		}
	}

	void MenuPrincipal::setFichiers(bool sauvegardeExistante)
	{
		sauvegardeExistante_ = sauvegardeExistante;
	}

	int MenuPrincipal::run()
	{
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (fenetre_->pollEvent(event))
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				fenetre_->close();
		}
		fenetre_->clear(sf::Color::Black);

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
			return choix_;
		}

		if (!sauvegardeExistante_) // charger grisé
		{
			TabMenu_[2].setFillColor(gris_);
		}
		else
		{
			TabMenu_[2].setFillColor(sf::Color::White);
		}
		TabMenu_[choix_].setFillColor(sf::Color::Yellow);
		// c'est ici qu'on dessine tout
		// window.draw(...);
		for (int i = 0; i < 4; i++)
		{
			fenetre_->draw(TabMenu_[i]);
		}

		fenetre_->draw(titre_);

		titre_.setTextureRect(animationtitre_.getFrame());


		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		fenetre_->display();

		return 0;
	}
	//return 3;

}

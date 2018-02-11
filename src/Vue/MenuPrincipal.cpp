#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "MenuPrincipal.h"

namespace Vue
{

	MenuPrincipal::MenuPrincipal(sf::RenderWindow* fenetre) : GameState(fenetre), frame(-1), choix(0), toucheLache(true), fichiers(false)
	{	//Titre est une texture donc il a un constructeur par défaut et n'a pas besoin d'être initialisé

		fenetre->setVerticalSyncEnabled(true);
		fenetre->setFramerateLimit(12);


		if (!titre.loadFromFile("ressources/sprite/titre.png"))
		{
			std::cout << "error img titre" << std::endl;
		}
		titre.setSmooth(false);

		sprite.setTexture(titre);

		animation[0] = sf::IntRect(0, 0, 512, 256);  // Meme chose pour les tableaux de IntRect
		animation[1] = sf::IntRect(0, 256, 512, 256);
		animation[2] = sf::IntRect(0, 256 * 2, 512, 256);
		animation[3] = sf::IntRect(0, 256 * 3, 512, 256);
		animation[4] = sf::IntRect(0, 256 * 4, 512, 256);
		animation[5] = sf::IntRect(0, 256 * 5, 512, 256);
		animation[6] = sf::IntRect(0, 256 * 6, 512, 256);
		animation[7] = sf::IntRect(0, 256 * 7, 512, 256);
		animation[8] = sf::IntRect(0, 256 * 8, 512, 256);
		animation[9] = sf::IntRect(0, 256 * 9, 512, 256);
		animation[10] = sf::IntRect(0, 256 * 10, 512, 256);


		sprite.setPosition(300, 100);

		// GESTION DE L'ECRITURE

		if (!font.loadFromFile("ressources/VCR_OSD_MONO_1.001.ttf"))
		{
			std::cout << "error font" << std::endl;
		}

		TabMenu[0].setString("Nouveau");
		TabMenu[1].setString("Rejoindre");
		TabMenu[2].setString("Charger");
		TabMenu[3].setString("Quitter");

		for (int i = 0; i < 4; i++)
		{
			TabMenu[i].setFont(font);// choix de la police à utiliser
			TabMenu[i].setCharacterSize(24);// choix de la taille des caractères
			TabMenu[i].setFillColor(sf::Color::White);
			TabMenu[i].setPosition(450, i * 50 + 400);
		}

	}

	void MenuPrincipal::setFichiers(bool fichiersExistant)
	{
		fichiers = fichiersExistant;
	}

	int MenuPrincipal::run()
	{
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (fenetre_->pollEvent(event))
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				return 4;
		}
		fenetre_->clear(sf::Color::Black);

		frame = frame + 1;
		if (frame == 11)
		{
			frame = 0;
			std::cout << std::endl;
		}
		std::cout << frame;

		TabMenu[choix].setFillColor(sf::Color::White);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && toucheLache)
		{
			if (choix > 0)
			{
				if (!fichiers && choix == 3)
				{
					choix -= 2;
				}
				else
				{
					choix -= 1;
				}
			}
			toucheLache = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && toucheLache)
		{
			if (choix < 3)
			{
				if (!fichiers && choix == 1)
				{
					choix += 2;
				}
				else
				{
					choix += 1;
				}
			}
			toucheLache = false;
		}

		if (event.type == sf::Event::KeyReleased)
		{
			toucheLache = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			return choix;
		}

		if (!fichiers) // charger grisé
		{
			TabMenu[2].setFillColor(gris);
		}
		else
		{
			TabMenu[2].setFillColor(sf::Color::White);
		}
		TabMenu[choix].setFillColor(sf::Color::Yellow);
		// c'est ici qu'on dessine tout
		// window.draw(...);
		for (int i = 0; i < 4; i++)
		{
			fenetre_->draw(TabMenu[i]);
		}

		fenetre_->draw(sprite);

		sprite.setTextureRect(animation[frame]);
		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		fenetre_->display();

		return 0;
	}
	//return 3;

}

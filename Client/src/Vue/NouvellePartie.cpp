#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "NouvellePartie.h"

namespace Vue
{

	NouvellePartie::NouvellePartie(sf::RenderWindow* fenetre) : GameState(fenetre), frame(-1), choix(1), toucheLache(true) {
		fenetre->setVerticalSyncEnabled(true);
		fenetre->setFramerateLimit(12);

		chaineNom = "Nom de la partie : ";
		if (!titre.loadFromFile("ressources/sprite/titre.png"))
		{
			std::cout << "error img titre" << std::endl;
		}
		titre.setSmooth(false);
		sprite.setTexture(titre);

		sf::IntRect animation[11];
		animation[0] = sf::IntRect(0, 0, 256, 512);
		animation[1] = sf::IntRect(256, 0, 256, 512);
		animation[2] = sf::IntRect(512, 0, 256, 512);
		animation[3] = sf::IntRect(1024, 0, 256, 512);
		animation[4] = sf::IntRect(2048, 0, 256, 512);
		animation[5] = sf::IntRect(2048 * 2, 0, 256, 512);
		animation[6] = sf::IntRect(2048 * 4, 0, 256, 512);
		animation[7] = sf::IntRect(2048 * 8, 0, 256, 512);
		animation[8] = sf::IntRect(2048 * 16, 0, 256, 512);
		animation[9] = sf::IntRect(2048 * 32, 0, 256, 512);
		animation[10] = sf::IntRect(2048 * 64, 0, 256, 512);

		sprite.setPosition(270, -50);

		// GESTION DE L'ECRITURE
		if (!font.loadFromFile("ressources/VCR_OSD_MONO_1.001.ttf"))
		{
			std::cout << "error font" << std::endl;
		}

		TabMenu[0].setString("Creer");
		TabMenu[1].setString(chaineNom);
		TabMenu[2].setString("Retour");
		titreCrea.setString("Nouvelle partie");

		for (int i = 0; i < 3; i++)
		{
			TabMenu[i].setFont(font);// choix de la police à utiliser
			TabMenu[i].setCharacterSize(24);// choix de la taille des caractères
			TabMenu[i].setFillColor(sf::Color::White);
			TabMenu[i].setPosition(310, i * 50 + 320);
		}

		//FIN GESTION DE L'ECRITURE
	}
	int NouvellePartie::run() {
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (fenetre_->pollEvent(event))
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				return 3;
		}
		fenetre_->clear(sf::Color::Black);

		frame = frame + 1;
		if (frame == 11)
		{
			frame = 0;
		}

		sprite.setTextureRect(sf::IntRect(0, 256 * frame, 512, 256));

		TabMenu[choix].setFillColor(sf::Color::White);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && toucheLache)
		{
			if (choix > 0)
			{
				choix -= 1;
			}
			toucheLache = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && toucheLache)
		{
			if (choix < 2)
			{
				choix += 1;
			}
			toucheLache = false;
		}

		if (event.type == sf::Event::TextEntered)
		{
			if (choix == 1)
			{

				if (event.type == sf::Event::TextEntered && chaineNom.size() < 30 && !sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					// Handle ASCII characters only
					if (event.text.unicode < 128)
					{
						chaineNom += static_cast<char>(event.text.unicode);
						TabMenu[1].setString(chaineNom);
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && chaineNom.size() > 19)
				{
					chaineNom.erase(chaineNom.end() - 1);
					TabMenu[1].setString(chaineNom);
				}
			}
			else if (choix == 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				return 3;
			}
			toucheLache = false;
		}

		if (event.type == sf::Event::KeyReleased)
		{
			toucheLache = true;
		}
		titreCrea.setFont(font);// choix de la police à utiliser
		titreCrea.setCharacterSize(36);// choix de la taille des caractères
		titreCrea.setFillColor(sf::Color::White);
		titreCrea.setPosition(350, 230);
		fenetre_->draw(titreCrea);

		numIP.setFont(font);// choix de la police à utiliser
		numIP.setCharacterSize(24);// choix de la taille des caractères
		numIP.setFillColor(sf::Color::White);
		numIP.setPosition(30, 650);
		fenetre_->draw(numIP);


		TabMenu[choix].setFillColor(sf::Color::Yellow);
		// c'est ici qu'on dessine tout
		// window.draw(...);
		for (int i(0); i < 3; i++)
		{
			fenetre_->draw(TabMenu[i]);
		}

		fenetre_->draw(sprite);

		sprite.setTextureRect(animation[frame]);
		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		fenetre_->display();
		return 0;
	}

	void NouvellePartie::setIP(std::string str) {
		numIP.setString(str);
	}

	std::string NouvellePartie::getIP() {
		return numIP.getString();

	}

}
#pragma once

#include "Curseur.hpp"
#include <iostream>
#include "Unite.hpp"
#include "InfoPersonnageUI.hpp"
#include "GameState.hpp"

class VueCombat : GameState
{
public:

	VueCombat(sf::RenderWindow* window): GameState(window), unite_(sf::Vector2i(4, 3)), 
										grille_(LONGUEUR_GRILLE, std::vector<sf::Sprite>(LARGEUR_GRILLE, sf::Sprite()))
	{
		

		textureSol_.loadFromFile("ressources/sprite/ground_tiles.png");
		textureSol_.setSmooth(true);

		
		for (int i(0); i < LONGUEUR_GRILLE; i++)
		{
			for (int j(0); j < LARGEUR_GRILLE; j++)
			{
				sf::Sprite* sprite = &grille_[i][j];
				sprite->setTexture(textureSol_);
				sprite->setTextureRect(sf::IntRect(32, 64, 32, 32));
				sprite->setPosition(i * 32, j * 32);
			}
		}
	}

	void run() override
	{
		sf::Event event;
		while (window_->pollEvent(event))
		{
			// fermeture de la fen�tre lorsque l'utilisateur le souhaite
			switch (event.type)
			{
			case sf::Event::Closed:
				window_->close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Z:
					curseur_.deplacementCurseur(curseur_.getPosition() + sf::Vector2i(0, -1));
					break;
				case sf::Keyboard::Q:
					curseur_.deplacementCurseur(curseur_.getPosition() + sf::Vector2i(-1, 0));
					break;
				case sf::Keyboard::S:
					curseur_.deplacementCurseur(curseur_.getPosition() + sf::Vector2i(0, 1));
					break;
				case sf::Keyboard::D:
					curseur_.deplacementCurseur(curseur_.getPosition() + sf::Vector2i(1, 0));
					break;
				default: break;


				}

			}
		}

		// effacement de la fen�tre en noir
		window_->clear(sf::Color::Black);

		for (auto colone : grille_)
		{
			for (sf::Sprite sprite : colone)
			{
				window_->draw(sprite);
			}
		}

		window_->draw(curseur_);
		window_->draw(unite_);
		window_->draw(infoPersonnageUI_);

		// fin de la frame courante, affichage de tout ce qu'on a dessin�
		window_->display();
	}

protected:

	const int LONGUEUR_GRILLE = 10;
	const int LARGEUR_GRILLE = 10;

	std::vector<std::vector<sf::Sprite>> grille_;

	Unite unite_;
	Curseur curseur_;
	InfoPersonnageUI infoPersonnageUI_;
	sf::Texture textureSol_;


};
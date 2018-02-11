#pragma once

#include "Curseur.h"
#include <iostream>
#include "Unite.hpp"
#include "InfoPersonnageUI.h"
#include "GameState.h"
#include "../Modele/Vecteur2.h"

class VueCombat : GameState
{
public:



	VueCombat(sf::RenderWindow* window): GameState(window), 
										grille_(LONGUEUR_GRILLE, std::vector<sf::Sprite>(LARGEUR_GRILLE, sf::Sprite()))
	{
		textureSol_.loadFromFile("ressources/sprite/map.png");
		textureSol_.setSmooth(true);

		ajouterUnite("Archer1","ressources/sprite/Archer_sprite.png", sf::Vector2i(4, 3));
		
		for (int i(0); i < LONGUEUR_GRILLE; i++)
		{
			for (int j(0); j < LARGEUR_GRILLE; j++)
			{
				sf::Sprite* sprite = &grille_[i][j];
				sprite->setTexture(textureSol_);
				sprite->setTextureRect(sf::IntRect(0, 0, 64, 64));
				sprite->setPosition(i * 64, j * 64);
			}
		}
	}

	~VueCombat()
	{
		auto iterateur = textures_.begin();
		while(iterateur != textures_.end())
		{
			delete iterateur->second;
			++iterateur;
		}
	}

	int run() override
	{
		sf::Event event;
		while (fenetre_->pollEvent(event))
		{
			// fermeture de la fen�tre lorsque l'utilisateur le souhaite
			switch (event.type)
			{
			case sf::Event::Closed:
				fenetre_->close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Z:
					curseur_.deplacerCurseur(sf::Vector2i(0, -1));
					break;
				case sf::Keyboard::Q:
					curseur_.deplacerCurseur(sf::Vector2i(-1, 0));
					break;
				case sf::Keyboard::S:
					curseur_.deplacerCurseur(sf::Vector2i(0, 1));
					break;
				case sf::Keyboard::D:
					curseur_.deplacerCurseur(sf::Vector2i(1, 0));
					break;
				default: break;


				}

			}
		}

		// effacement de la fen�tre en noir
		fenetre_->clear(sf::Color::Black);

		for (auto colone : grille_)
		{
			for (sf::Sprite sprite : colone)
			{
				fenetre_->draw(sprite);
			}
		}

		fenetre_->draw(curseur_);
		for(Unite unite : unites_)
			fenetre_->draw(unite);
		fenetre_->draw(infoPersonnageUI_);

		// fin de la frame courante, affichage de tout ce qu'on a dessin�
		fenetre_->display();
		return 0;
	}

	void ajouterUnite(std::string nom ,std::string cheminTexture, Vecteur2<int> position)
	{
		sf::Texture* texture;
		if (textures_.find(cheminTexture) == textures_.end())
		{
			sf::Image image;
			image.loadFromFile(cheminTexture);
			image.createMaskFromColor(sf::Color::Transparent, 0);
			
			texture = new sf::Texture;
			texture->loadFromImage(image);
		}
		else
		{
			texture = textures_[cheminTexture];
		}
		
		unites_.push_back(Unite(nom, texture, position));
	}

	void deplacerUnite(std::string nom, Vecteur2<int> position)
	{
		Unite* unite = nullptr;

		auto iterateur = unites_.begin();
		while (iterateur != unites_.end())
		{
			if(iterateur->getNom() == nom)
			{
				unite = &*iterateur;
				std::cout << "a" << std::endl;
				break;
			}
			++iterateur;
		}
		if (iterateur == unites_.end()) return;
		unite->setPosition(position);
		std::cout << "b" << std::endl;
	}


protected:

	std::map<std::string, sf::Texture*> textures_;
	
	const int LONGUEUR_GRILLE = 10;
	const int LARGEUR_GRILLE = 10;

	std::vector<std::vector<sf::Sprite>> grille_;

	std::vector<Unite> unites_;
	Curseur curseur_;
	InfoPersonnageUI infoPersonnageUI_;
	sf::Texture textureSol_;


};
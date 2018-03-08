#pragma once

#include "Unite.h"

namespace Vue
{

		Unite::Unite(Modele::Unite* unite, sf::Texture* texture) : texture_(texture), modele_(unite)
		{
			sprite_ = new sf::Sprite();
			sprite_->setPosition(modele_->getPosition().x * 64, modele_->getPosition().y * 64);
			sprite_->setTexture(*texture_);
			sprite_->setTextureRect(sf::IntRect(0, 0, 64, 64));
			initAnimation();
		}

		Unite::~Unite()
		{
			//delete sprite_;
		}

		void Unite::initAnimation()
		{
			const std::vector < sf::IntRect > idle =
			{
				sf::IntRect(0, 256, 64, 64),
				sf::IntRect(64, 256, 64, 64)
			};
			idle_.initialiser(idle, 750);

			const std::vector < sf::IntRect > deplacementFace =
			{
				sf::IntRect(0, 0, 64, 64) ,
				sf::IntRect(64, 0, 64, 64) ,
				sf::IntRect(128, 0, 64, 64) ,
				sf::IntRect(192, 0, 64, 64) ,
				sf::IntRect(256, 0, 64, 64) ,
				sf::IntRect(320, 0, 64, 64) ,
				sf::IntRect(384, 0, 64, 64) ,
				sf::IntRect(448, 0, 64, 64)
			};
			deplacementFace_.initialiser(deplacementFace, 500);

			const std::vector < sf::IntRect > deplacementDos =
			{
				sf::IntRect(0, 64, 64, 64) ,
				sf::IntRect(64, 64, 64, 64) ,
				sf::IntRect(128, 64, 64, 64) ,
				sf::IntRect(192, 64, 64, 64) ,
				sf::IntRect(256, 64, 64, 64) ,
				sf::IntRect(320, 64, 64, 64) ,
				sf::IntRect(384, 64, 64, 64) ,
				sf::IntRect(448, 64, 64, 64)
			};
			deplacementDos_.initialiser(deplacementFace, 500);
		}

	void Unite::deplacerUnite(Modele::Vecteur2<int> deplacement)
	{
		std::cout << std::to_string(deplacement) << std::endl;
			sprite_->move(sf::Vector2f(deplacement.x * 64, deplacement.y * 64));
	}

	void Unite::setPosition(Modele::Vecteur2<int> position)
	{
		sprite_->setPosition(position.x*64, position.y*64);
	}


	void Unite::dessiner(sf::RenderTarget* cible, sf::RenderStates etat)
	{
		sprite_->setTextureRect(idle_.getFrame());
		cible->draw(*sprite_, etat);
	}


	const std::map<const Modele::Classe, const std::string> Unite::cheminTextureUnite =
	{
		{ Modele::Classe::Tank, "ressources/sprite/Tank_sprite.png" },
	{ Modele::Classe::Archer, "ressources/sprite/Archer_sprite.png" },
	{ Modele::Classe::Soldat, "ressources/sprite/Soldat_sprite.png" }
	};

}

#pragma once

#include "Unite.h"

namespace Vue
{

		Unite::Unite(Modele::Unite* unite, sf::Texture* texture) : texture_(texture), modele_(unite)
		{
			sprite_ = new sf::Sprite();
			sprite_->setPosition(modele_->getPosition().x * RES_TEXTURE_XSB, modele_->getPosition().y * RES_TEXTURE_XSB);
			sprite_->setTexture(*texture_);
			sprite_->setTextureRect(sf::IntRect(0, 0, RES_TEXTURE_XSB, RES_TEXTURE_XSB));
			initAnimation();
		}

		Unite::~Unite()
		{
			//delete sprite_;
		}

		void Unite::initAnimation()
		{
			int equipe = modele_->getEquipe()._to_integral()*2;

			const std::vector < sf::IntRect > idle =
			{
				sf::IntRect(equipe* RES_TEXTURE_XSB, 4*RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB),
				sf::IntRect(equipe * RES_TEXTURE_XSB+ RES_TEXTURE_XSB , 4*RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB)
			};
			idle_.initialiser(idle, 750);

			const std::vector < sf::IntRect > deplacementFace =
			{
				sf::IntRect(0, equipe * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(2*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(3*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(4*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(5*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(6*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(7*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB)
			};
			deplacementFace_.initialiser(deplacementFace, 500);

			const std::vector < sf::IntRect > deplacementDos =
			{
				sf::IntRect(0, RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB+RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(2*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB + RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(3*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB + RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(4*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB + RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(5*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB + RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(6*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB + RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
				sf::IntRect(7*RES_TEXTURE_XSB, equipe * RES_TEXTURE_XSB + RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB)
			};
			deplacementDos_.initialiser(deplacementFace, 500);
		}

	void Unite::deplacerUnite(Modele::Vecteur2<int> deplacement)
	{
		sprite_->move(sf::Vector2f(deplacement.x * RES_TEXTURE_XSB, deplacement.y * RES_TEXTURE_XSB));
	}

	void Unite::setPosition(Modele::Vecteur2<int> position)
	{
		sprite_->setPosition(position.x*RES_TEXTURE_XSB, position.y*RES_TEXTURE_XSB);
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

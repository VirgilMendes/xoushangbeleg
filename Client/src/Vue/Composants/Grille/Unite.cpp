#pragma once

#include "Unite.h"
#include <memory.h>

namespace Vue
{

	Unite::Unite(Modele::Unite* unite, sf::Texture* texture) : texture_(texture), modele_(unite)
	{
		mort = false;

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
		idle_.initialiser(idle, 750, Animation::Type::Boucle);

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
		deplacementFace_.initialiser(deplacementFace, 50, Animation::Type::UneFois);

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
		deplacementDos_.initialiser(deplacementDos, 50, Animation::Type::UneFois);
		const std::vector < sf::IntRect > attaque =
		{
			sf::IntRect((RES_TEXTURE_XSB * 4) + 0, 5 * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
			sf::IntRect((RES_TEXTURE_XSB * 4) + RES_TEXTURE_XSB, 5 * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
			sf::IntRect((RES_TEXTURE_XSB * 4) + 2 * RES_TEXTURE_XSB, 5 * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
			sf::IntRect((RES_TEXTURE_XSB * 4) + 3 * RES_TEXTURE_XSB, 5 * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB) ,
		};//equipe*
		attaque_.initialiser(attaque, 50, Animation::Type::UneFois);
	}

	bool Unite::deplacerUniteVers(Modele::Vecteur2<int> cible)
	{
		
		sf::Vector2f position = sprite_->getPosition();
		if (position == sf::Vector2f(cible.x * 64, cible.y * 64)) return  true;
		if((static_cast<int>(position.x) % 64 == 0) && (static_cast<int>(position.y) % 64 == 0))
		{
			if (position.x > cible.x * RES_TEXTURE_XSB)
			{
				animationDeplacementCourante_ = &deplacementDos_;
			}
			else if (position.x < cible.x * RES_TEXTURE_XSB)
			{
				animationDeplacementCourante_ = &deplacementFace_;
			}
			else if (position.y > cible.y * RES_TEXTURE_XSB)
			{
				animationDeplacementCourante_ = &deplacementDos_;
			}
			else if (position.y < cible.y * RES_TEXTURE_XSB)
			{
				animationDeplacementCourante_ = &deplacementFace_;
			}
			animationDeplacementCourante_->restart();
		}		
		sf::IntRect frame = animationDeplacementCourante_->getFrame();
		if (frame != sprite_->getTextureRect())
		{	
			
			sprite_->setTextureRect(frame);
			
			if (position.x > cible.x*RES_TEXTURE_XSB)
			{
				sprite_->move(-8,0);
			}
			else if (position.x < cible.x*RES_TEXTURE_XSB)
			{
				sprite_->move(8, 0);
			}
			else if (position.y > cible.y*RES_TEXTURE_XSB)
			{
				sprite_->move(0, -8);
			}
			else if (position.y < cible.y*RES_TEXTURE_XSB)
			{
				sprite_->move(0, 8);
			}
		}
		return false;
	}
	bool Unite::attaquer()
	{
		animationDeplacementCourante_ = &attaque_;
		sf::IntRect frame = animationDeplacementCourante_->getFrame();
		int equipe = modele_->getEquipe()._to_integral() * 2;
		if (frame != sprite_->getTextureRect())
		{
			sprite_->setTextureRect(frame);
			return false;

		}
		return true;

	}

	void Unite::setPosition(Modele::Vecteur2<int> position)
	{
		sprite_->setPosition(position.x, position.y);
	}

	Modele::Vecteur2<int> Unite::getPosition()
	{
		sf::Vector2f i = sprite_->getPosition();
		return sf::Vector2i(i.x, i.y);
	}

	void Unite::mourrir()
	{
		this->mort = true;
		if (modele_->getEquipe() == Modele::Equipe::Rouge)
		{
			sprite_->setTextureRect(sf::IntRect(4*RES_TEXTURE_XSB,4* RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB));
		}
		else
		{
			sprite_->setTextureRect(sf::IntRect(5 * RES_TEXTURE_XSB, 4 * RES_TEXTURE_XSB, RES_TEXTURE_XSB, RES_TEXTURE_XSB));
		}
	}

	void Unite::update()
	{
		if (!mort)
		{
			sprite_->setTextureRect(idle_.getFrame());
		}
	}


	void Unite::dessiner(sf::RenderTarget* cible, sf::RenderStates etat)
	{
		cible->draw(*sprite_, etat);
	}


	const std::map<const Modele::Classe, const std::string> Unite::cheminTextureUnite =
	{
		{ Modele::Classe::Tank, "ressources/sprite/Tank_sprite.png" },
	{ Modele::Classe::Archer, "ressources/sprite/Archer_sprite.png" },
	{ Modele::Classe::Soldat, "ressources/sprite/Soldat_sprite.png" }
	};

}

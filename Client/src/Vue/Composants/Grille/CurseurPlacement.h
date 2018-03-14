
#pragma once
#include <SFML/Graphics.hpp>
#include "../../Outils/Animation.h"
#include <iostream>
#include "../../Constante.h"

namespace Vue
{

	class CurseurPlacement : public sf::Drawable
	{
	public:
		CurseurPlacement() : position_(0, 0), sprite_(nullptr), texture_(nullptr)
		{
			sprite_ = new sf::Sprite();
			texture_ = new sf::Texture();
			if (!texture_->loadFromFile("ressources/sprite/AnimCurseur.png"))
			{
				std::cout << "erreur chargement Texture AnimCurseur.png" << std::endl;
			}

			sprite_->setPosition(position_.x, position_.y);
			sprite_->setTexture(*texture_);
			sprite_->scale(3.0f, 3.0f);
			sprite_->setTextureRect(sf::IntRect(0, 0, RES_TEXTURE_XSB, RES_TEXTURE_XSB));
			initAnimation();
		}

		CurseurPlacement(sf::Vector2i position) : position_(position), sprite_(nullptr), texture_(nullptr)
		{
			sprite_ = new sf::Sprite();
			texture_ = new sf::Texture();
			if (!texture_->loadFromFile("ressources/sprite/AnimCurseur.png"))
			{
				std::cout << "erreur chargement Texture AnimCurseur.png" << std::endl;
			}

			sprite_->setPosition(position_.x, position_.y);
			sprite_->setTexture(*texture_);
			sprite_->setTextureRect(sf::IntRect(0, 0, RES_TEXTURE_XSB, RES_TEXTURE_XSB));
			sprite_->scale(4.0f, 4.0f);
			initAnimation();
		}


		void initAnimation()
		{
			const std::vector < sf::IntRect > stay =
			{
				sf::IntRect(0, 0, RES_TEXTURE_XSB, RES_TEXTURE_XSB),
				sf::IntRect(RES_TEXTURE_XSB, 0, RES_TEXTURE_XSB, RES_TEXTURE_XSB),
				sf::IntRect(2 * RES_TEXTURE_XSB, 0, RES_TEXTURE_XSB, RES_TEXTURE_XSB),
				sf::IntRect(3 * RES_TEXTURE_XSB, 0, RES_TEXTURE_XSB, RES_TEXTURE_XSB),
				sf::IntRect(4 * RES_TEXTURE_XSB, 0, RES_TEXTURE_XSB, RES_TEXTURE_XSB),
				sf::IntRect(5 * RES_TEXTURE_XSB, 0, RES_TEXTURE_XSB, RES_TEXTURE_XSB),
				sf::IntRect(6 * RES_TEXTURE_XSB, 0, RES_TEXTURE_XSB, RES_TEXTURE_XSB),
				sf::IntRect(7 * RES_TEXTURE_XSB, 0, RES_TEXTURE_XSB, RES_TEXTURE_XSB)
			};
			stay_.initialiser(stay, 100);

		}

		void deplacerCurseur(sf::Vector2i positionRelative)
		{
			position_ += positionRelative;
			sprite_->setPosition(position_.x, position_.y);
		}
		void setPosition(sf::Vector2i position)
		{
			position_ = position;
			sprite_->setPosition(position.x, position.y);
		}

		sf::Vector2i getPosition() { return position_; }


	private:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			sprite_->setTextureRect(stay_.getFrame());
			target.draw(*sprite_, states);
		}

		Animation stay_;

		sf::Vector2i position_;
		sf::Texture* texture_;
		sf::Sprite* sprite_;
	};
}
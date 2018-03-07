#pragma once
#include <SFML/Graphics.hpp>
#include "../Outils/Animation.h"
#include <iostream>

namespace Vue
{

	class Curseur : public sf::Drawable
	{
	public:
		Curseur() : position_(0, 0), sprite_(nullptr), texture_(nullptr)
		{
			sprite_ = new sf::Sprite();
			texture_ = new sf::Texture();
			if (!texture_->loadFromFile("ressources/sprite/AnimCurseur.png"))
			{
				std::cout << "erreur chargement Texture AnimCurseur.png" << std::endl;
			}

			sprite_->setPosition(position_.x * 64, position_.y * 64);
			sprite_->setTexture(*texture_);
			sprite_->setTextureRect(sf::IntRect(0, 0, 64, 64));
			initAnimation();
		}

		Curseur(sf::Vector2i position) : position_(position), sprite_(nullptr),texture_(nullptr)
		{
			sprite_ = new sf::Sprite();
			texture_ = new sf::Texture();
			if(!texture_->loadFromFile("ressources/sprite/AnimCurseur.png"))
			{
				std::cout << "erreur chargement Texture AnimCurseur.png" << std::endl;
			}

			sprite_->setPosition(position_.x * 64, position_.y * 64);
			sprite_->setTexture(*texture_);
			sprite_->setTextureRect(sf::IntRect(0, 0, 64, 64));
			initAnimation();
		}


		void initAnimation()
		{
			const std::vector < sf::IntRect > stay =
			{
				sf::IntRect(0, 0, 64, 64),
				sf::IntRect(64, 0, 64, 64),
				sf::IntRect(128, 0, 64, 64),
				sf::IntRect(192, 0, 64, 64),
				sf::IntRect(256, 0, 64, 64),
				sf::IntRect(320, 0, 64, 64),
				sf::IntRect(384, 0, 64, 64),
				sf::IntRect(448, 0, 64, 64)
			};
			stay_.initialiser(stay, 100);

		}

		void deplacerCurseur(sf::Vector2i positionRelative)
		{
			position_ += positionRelative;
			sprite_->setPosition(position_.x * 64, position_.y * 64);
		}
		void setPosition(sf::Vector2i position)
		{
			position_ = position;
			sprite_->setPosition(position.x * 64, position.y * 64);
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
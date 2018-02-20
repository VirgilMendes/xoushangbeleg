#pragma once

#include <SFML/Graphics.hpp>
#include "../Outils/Animation.h"

namespace Vue
{

	class Unite : public sf::Drawable
	{
	public:
		Unite(std::string nom, sf::Texture* texture) : position_(0, 0), texture_(texture), nom_(nom), sprite_(nullptr)
		{
			sprite_ = new sf::Sprite();
			sprite_->setPosition(position_.x * 64, position_.y * 64);
			sprite_->setTexture(*texture_);
			sprite_->setTextureRect(sf::IntRect(0, 0, 64, 64));
			initAnimation();
		}

		Unite(std::string nom, sf::Texture* texture, sf::Vector2i position) : texture_(texture), position_(position), nom_(nom), sprite_(nullptr)
		{
			sprite_ = new sf::Sprite();
			sprite_->setPosition(position_.x * 64, position_.y * 64);
			sprite_->setTexture(*texture_);
			sprite_->setTextureRect(sf::IntRect(0, 0, 64, 64));
			initAnimation();
		}

		~Unite()
		{
			//delete sprite_;
		}

		void initAnimation()
		{
			const std::vector < sf::IntRect > idle = 
			{
				sf::IntRect(0, 192, 64, 64),
				sf::IntRect(64, 192, 64, 64)
			};
			idle_.initialiser(idle, 1000);

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
			deplacementFace_.initialiser(deplacementFace, 1000);

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
			deplacementDos_.initialiser(deplacementFace, 1000);
		}


		sf::Vector2i getPosition() { return position_; }
		void setPosition(sf::Vector2i position) { position_ = position; sprite_->setPosition(position_.x * 64, position_.y * 64); }
		std::string getNom() { return nom_; }

	private:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			sprite_->setTextureRect(idle_.getFrame());
			target.draw(*sprite_, states);
		}

		Animation idle_; 
		Animation deplacementFace_;
		Animation deplacementDos_;
		std::string nom_;
		sf::Vector2i position_;
		sf::Sprite* sprite_;
		sf::Image image_;
		sf::Texture* texture_;
	};

}

#pragma once

#include <SFML/Graphics.hpp>

namespace Vue
{

	class Unite : public sf::Drawable
	{
	public:
		Unite(std::string nom, sf::Texture* texture) : position_(0, 0), texture_(texture), nom_(nom)
		{
			sprite_.setPosition(position_.x * 64, position_.y * 64);
			sprite_.setTexture(*texture_);
			sprite_.setTextureRect(sf::IntRect(0, 0, 64, 64));
		}

		Unite(std::string nom, sf::Texture* texture, sf::Vector2i position) : texture_(texture), position_(position), nom_(nom)
		{
			sprite_.setPosition(position_.x * 64, position_.y * 64);
			sprite_.setTexture(*texture_);
			sprite_.setTextureRect(sf::IntRect(0, 0, 64, 64));
		}

		sf::Vector2i getPosition() { return position_; }
		void setPosition(sf::Vector2i position) { position_ = position; sprite_.setPosition(position_.x * 64, position_.y * 64); }
		std::string getNom() { return nom_; }

	private:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			target.draw(sprite_, states);
		}

		std::string nom_;
		sf::Vector2i position_;
		sf::Sprite sprite_;
		sf::Image image_;
		sf::Texture* texture_;
	};

}
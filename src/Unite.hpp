#pragma once

#pragma once
#include <SFML/Graphics.hpp>

class Unite : public sf::Drawable
{
public:
	Unite(sf::Texture* texture) : position_(0, 0), texture_(texture)
	{
		sprite_.setPosition(position_.x * 64, position_.y * 64);
		sprite_.setTexture(*texture_);
		sprite_.setTextureRect(sf::IntRect(0,0,64,64));
	}

	Unite(sf::Texture* texture, sf::Vector2i position) : texture_(texture), position_(position)
	{
		sprite_.setPosition(position_.x * 64, position_.y * 64);
		sprite_.setTexture(*texture_);
		sprite_.setTextureRect(sf::IntRect(0, 0, 64, 64));
	}

	sf::Vector2i getPosition() { return position_; }


private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite_, states);
	}

	sf::Vector2i position_;
	sf::Sprite sprite_;
	sf::Image image_;
	sf::Texture* texture_;
};
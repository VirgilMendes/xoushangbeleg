#pragma once

#pragma once
#include <SFML/Graphics.hpp>

class Unite : public sf::Drawable
{
public:
	Unite() : position_(0, 0), forme_(sf::Vector2f(32, 32))
	{
		image_.loadFromFile("ressources/sprite/Archer_sprite.png");
		image_.createMaskFromColor(sf::Color::Transparent, 0);

		texture_.loadFromImage(image_);

		forme_.setPosition(position_.x * 32, position_.y * 32);
		forme_.setTexture(&texture_);
		forme_.setTextureRect(sf::IntRect(0,0,50,50));
	}

	Unite(sf::Vector2i position) : position_(position), forme_(sf::Vector2f(32, 32))
	{
		image_.loadFromFile("ressources/sprite/Archer_sprite.png");
		image_.createMaskFromColor(sf::Color::Transparent, 0);

		texture_.loadFromImage(image_);

		forme_.setPosition(position_.x * 32, position_.y * 32);
		forme_.setTexture(&texture_);
		forme_.setTextureRect(sf::IntRect(0, 0, 50, 50));
	}

	void deplacementCurseur(sf::Vector2i position)
	{
		position_ = position;
		forme_.setPosition(position.x * 32, position.y * 32);
	}

	sf::Vector2i getPosition() { return position_; }


private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(forme_, states);
	}

	sf::Vector2i position_;
	sf::RectangleShape forme_;
	sf::Image image_;
	sf::Texture texture_;
};
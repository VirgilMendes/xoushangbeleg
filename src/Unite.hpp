#pragma once

#pragma once
#include <SFML/Graphics.hpp>

class Unite : public sf::Drawable
{
public:
	Unite() : position_(0, 0), clock_(new sf::Clock())
	{
		image_.loadFromFile("ressources/sprite/Archer_sprite.png");
		image_.createMaskFromColor(sf::Color::Transparent, 0);

		texture_.loadFromImage(image_);

		idleAnimation_.push_back(sf::IntRect(0, 0, 64, 64));
		idleAnimation_.push_back(sf::IntRect(64, 0, 64, 64));
		idleAnimationState_ = &idleAnimation_.begin();

		sprite_ = new sf::Sprite;
		sprite_->setPosition(position_.x * 64, position_.y * 64);
		sprite_->setTexture(texture_);
		sprite_->setTextureRect(idleAnimation_[0]);
		
	}

	virtual ~Unite()
	{
		delete clock_;
		delete sprite_;
		delete idleAnimationState_;
	}

	Unite(sf::Vector2i position) : position_(position)
	{
		image_.loadFromFile("ressources/sprite/Archer_sprite.png");
		image_.createMaskFromColor(sf::Color::Transparent, 0);

		texture_.loadFromImage(image_);

		sprite_ = new sf::Sprite;
		sprite_->setPosition(position_.x * 64, position_.y * 64);
		sprite_->setTexture(texture_);
		sprite_->setTextureRect(sf::IntRect(0, 0, 64, 64));
	}

	sf::Vector2i getPosition() { return position_; }


private:
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		if (clock_ != nullptr && clock_->getElapsedTime().asSeconds() > 1)
		{
			idleAnimationState_->operator++();
			if (*idleAnimationState_ == idleAnimation_.end())
			{
				idleAnimationState_->_Compat(idleAnimation_.begin());
			}
			sprite_->setTextureRect(**idleAnimationState_);
			clock_->restart();
		}
		target.draw(*sprite_, states);
	}

	sf::Vector2i position_;
	sf::Sprite* sprite_;
	sf::Image image_;
	sf::Texture texture_;
	sf::Clock* clock_;

	std::vector<sf::IntRect> idleAnimation_;
	std::vector<sf::IntRect>::iterator* idleAnimationState_;
};
#pragma once

#include <SFML/Graphics.hpp>

namespace Vue
{

	class InfoPersonnageUI : public sf::Drawable
	{
	public:
		InfoPersonnageUI() : forme_(sf::Vector2f(500, 200))
		{
			image_.create(32, 32, sf::Color::Red);
			image_.createMaskFromColor(sf::Color::Red, 50);

			texture_.loadFromImage(image_);

			forme_.setTexture(&texture_);
			forme_.setPosition(5, 550);
		}

	private:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			target.draw(forme_, states);
		}

		sf::RectangleShape forme_;
		sf::Text pointDeVie_;
		sf::Text nom_;
		sf::Text attaque_;
		sf::Text defence_;
		sf::Text classe_;
		sf::Image image_;
		sf::Texture texture_;
	};
}
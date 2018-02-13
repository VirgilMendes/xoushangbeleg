#pragma once


#ifndef DEF_JAUGE
#define DEF_JAUGE
#include "SFML/Graphics.hpp"
#pragma once

#include <string>

namespace Vue
{

	class Jauge : public sf::Drawable
	{
	public:

		Jauge(sf::Vector2f pos, int maximum, sf::Vector2f taill);
		Jauge(sf::Vector2f pos, int maximum, int courant, sf::Vector2f taill);

		void setPosition(sf::Vector2f position);
		sf::Vector2f getPosition();

		void setTaille(sf::Vector2f taill);
		sf::Vector2f getTaille();

		void setValeurCourante(int courant);
		int getValeurCourante();

		void setValeurMax(int maximum);
		int getValeurMax();

	private:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		sf::Vector2f position;
		sf::Vector2f taille;
		sf::RectangleShape fond;
		sf::RectangleShape barre;
		double valeurCourante;
		double valeurMax;
	};

#endif

}
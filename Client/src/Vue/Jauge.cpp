#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "Jauge.h"

namespace Vue {

	Jauge::Jauge(sf::Vector2f pos, int maximum, sf::Vector2f taill) : sf::Drawable(),position(pos), valeurMax(maximum), valeurCourante(maximum), taille(taill)
	{
		fond.setSize(taill);
		barre.setSize(taill);
		fond.setOutlineThickness(1);
		fond.setOutlineColor(sf::Color::White);
		fond.setFillColor(sf::Color::Transparent);
		barre.setFillColor(sf::Color::Green);
		fond.setPosition(position);
		barre.setPosition(position);
	}

	Jauge::Jauge(sf::Vector2f pos, int maximum, int courant, sf::Vector2f taill) : sf::Drawable(), position(pos), valeurMax(maximum), valeurCourante(courant), taille(taill)
	{
		sf::Vector2f transition((valeurCourante*taill.x) / valeurMax, taill.y);
		barre.setSize(transition);
		fond.setSize(taill);
		fond.setOutlineThickness(1);
		fond.setOutlineColor(sf::Color::White);
		fond.setFillColor(sf::Color::Transparent);
		barre.setFillColor(sf::Color::Green);
		fond.setPosition(position);
		barre.setPosition(position);
	}


	void Jauge::setPosition(sf::Vector2f pos)
	{
		position = pos;
		fond.setPosition(position);
		barre.setPosition(position);
	}

	sf::Vector2f Jauge::getPosition()
	{
		return position;
	}

	void Jauge::setTaille(sf::Vector2f taill)
	{
		fond.setSize(taill);
		taille = taill;
		sf::Vector2f transition((valeurCourante*taill.x) / valeurMax, taill.y);
		barre.setSize(transition);
	}

	sf::Vector2f Jauge::getTaille()
	{
		return taille;
	}

	void Jauge::setValeurCourante(int courant)
	{
		valeurCourante = courant;
		if (valeurCourante > valeurMax / 2)
		{
			barre.setFillColor(sf::Color::Green);
		}
		if (valeurCourante < valeurMax / 2 && valeurCourante > valeurMax / 4)
		{
			barre.setFillColor(sf::Color::Yellow);
		}
		if (valeurCourante < valeurMax / 4)
		{
			barre.setFillColor(sf::Color::Red);
		}

		if ( courant <= 0)
		{
			valeurCourante = 0;
		}
		else
		{
			valeurCourante = courant;
		}
		sf::Vector2f transition((valeurCourante*taille.x) / valeurMax, taille.y);
		barre.setSize(transition);
	}

	int Jauge::getValeurCourante()
	{
		return  valeurCourante;
	}


	void Jauge::setValeurMax(int maximum)
	{
		valeurMax = maximum;
	}

	int Jauge::getValeurMax()
	{
		return valeurMax;
	}

	void Jauge::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(barre, states);
		target.draw(fond, states);
	}

}
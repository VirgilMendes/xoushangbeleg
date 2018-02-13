#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "Jauge.h"

Jauge::Jauge(sf::Vector2f pos, int largeur, int  hauteur, int maximum, sf::Vector2f taill) :position(pos), valeurMax(maximum), valeurCourante(maximum),
fond(sf::Vector2f(largeur, hauteur)), barre(sf::Vector2f(largeur - 1, hauteur - 1))
{
	fond.setSize(taill);
	barre.setSize(taill);
	fond.setOutlineThickness(1);
	fond.setOutlineColor(sf::Color::White);
	fond.setFillColor(sf::Color::Black);
	barre.setFillColor(sf::Color::Green);
	fond.setPosition(position);
	barre.setPosition(position);
}

Jauge::Jauge(sf::Vector2f pos, int largeur, int  hauteur, int maximum, int courant, sf::Vector2f taill) :position(pos), valeurMax(maximum), valeurCourante(courant),
fond(sf::Vector2f(largeur, hauteur)), barre(sf::Vector2f(largeur - 1, hauteur - 1))
{
	fond.setSize(taill);
	sf::Vector2f transition((valeurCourante*taill.x) / valeurMax, taill.y);
	barre.setSize(transition);

	fond.setOutlineThickness(1);
	fond.setOutlineColor(sf::Color::White);
	fond.setFillColor(sf::Color::Black);
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
		barre.setFillColor(sf::Color(170, 0, 0));
	}
	if (valeurCourante < valeurMax / 4)
	{
		barre.setFillColor(sf::Color::Red);
	}
	valeurCourante = courant;
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

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "InterfaceUnite.h"
#include "Jauge.h"


namespace Vue 
{
	InterfaceUnite::InterfaceUnite(Modele::Unite unite) : sf::Drawable() , unite(unite)
	{

	}

	void InterfaceUnite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//target.draw(barrevie, states);
		target.draw(fond, states);
	}

}
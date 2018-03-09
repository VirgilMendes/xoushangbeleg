#pragma once
#include "FiltreCase.h"
#include <iostream>

namespace Vue
{
	
	FiltreCase::FiltreCase(std::list<Modele::Vecteur2<int>> cases)
	{
		image_.create(RES_TEXTURE_XSB, RES_TEXTURE_XSB, sf::Color::Red);
		image_.createMaskFromColor(sf::Color::Red, 75);
		texture_ = new sf::Texture();
		texture_->loadFromImage(image_);
			
		sommets_.setPrimitiveType(sf::Quads);

		for (Modele::Vecteur2<int> coordronneesCase : cases)
		{
			sommets_.append(sf::Vertex
			(
				sf::Vector2f(coordronneesCase.x*RES_TEXTURE_XSB, coordronneesCase.y*RES_TEXTURE_XSB),
				sf::Vector2f(0,0)
			));
			sommets_.append(sf::Vertex
			(
				sf::Vector2f((coordronneesCase.x+1) * RES_TEXTURE_XSB, coordronneesCase.y * RES_TEXTURE_XSB),
				sf::Vector2f(0, RES_TEXTURE_XSB)
			)); 
			sommets_.append(sf::Vertex
			(
				sf::Vector2f((coordronneesCase.x + 1) * RES_TEXTURE_XSB, (coordronneesCase.y + 1) * RES_TEXTURE_XSB),
				sf::Vector2f(RES_TEXTURE_XSB,0)
			));
			sommets_.append(sf::Vertex
			(
				sf::Vector2f(coordronneesCase.x * RES_TEXTURE_XSB, (coordronneesCase.y + 1) * RES_TEXTURE_XSB),
				sf::Vector2f(RES_TEXTURE_XSB, RES_TEXTURE_XSB)
			));
		}
	}
	FiltreCase::~FiltreCase()
	{
		delete texture_;
	}

	void FiltreCase::dessiner(sf::RenderWindow* cible, sf::RenderStates& etat)
	{
		etat.texture = texture_;
		cible->draw(sommets_, etat);
	}

}

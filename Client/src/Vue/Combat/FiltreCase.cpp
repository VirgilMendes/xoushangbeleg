#pragma once
#include "FiltreCase.h"
#include <iostream>

namespace Vue
{
	
		FiltreCase::FiltreCase(std::list<Modele::Vecteur2<int>> cases)
		{
			image_.create(64, 64, sf::Color::Red);
			image_.createMaskFromColor(sf::Color::Red, 25);
			texture_ = new sf::Texture();
			texture_->loadFromImage(image_);
			
			sommets_.setPrimitiveType(sf::Quads);

			for (Modele::Vecteur2<int> coordronneesCase : cases)
			{
				sommets_.append(sf::Vertex
				(
					sf::Vector2f(coordronneesCase.x*64, coordronneesCase.y*64), 
					sf::Vector2f(0,0)
				));
				sommets_.append(sf::Vertex
				(
					sf::Vector2f((coordronneesCase.x+1) * 64, coordronneesCase.y * 64),
					sf::Vector2f(0,64)
				)); 
				sommets_.append(sf::Vertex
				(
					sf::Vector2f((coordronneesCase.x + 1) * 64, (coordronneesCase.y + 1) * 64),
					sf::Vector2f(64,0)
				));
				sommets_.append(sf::Vertex
				(
					sf::Vector2f(coordronneesCase.x * 64, (coordronneesCase.y + 1) * 64),
					sf::Vector2f(64, 64)
				));
			}
		}
		FiltreCase::~FiltreCase()
		{
			
		}

	void FiltreCase::dessiner(sf::RenderWindow* cible, sf::RenderStates etat)
	{
		etat.texture = texture_;
		cible->draw(sommets_);
	}

}

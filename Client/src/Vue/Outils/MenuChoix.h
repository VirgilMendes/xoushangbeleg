#pragma once
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Node.h"
#include <iostream>

namespace Vue
{
	struct Choix
	{
		Choix(){}
		Choix(bool actif, sf::Text& texte): actif(actif), texte(texte){}
		bool actif;
		sf::Text texte;
	};

	class MenuChoix : public Node
	{
	public:

		MenuChoix(std::vector<std::string> textes, sf::Font police, int tailletexte, sf::Vector2i position = sf::Vector2i(0, 0));
		~MenuChoix()
		{
			for (Choix* choix : textes_)
			{
				delete choix;
			}
		}

	private:
		
		//Methode de Node 
		void dessinerNode(sf::RenderTarget& target, const sf::Transform& transform) override
		{
			for(Choix* choix : textes_)
			{
				target.draw(choix->texte, transform);
			}
		}
		virtual void setPositionElements(sf::Vector2i position) override
		{
			for (int i(0); i < textes_.size(); i++)
			{
				textes_[i]->texte.setPosition(position.x, position.y);
				textes_[i]->texte.move(5, tailletexte_ * i);
			}
		}
		virtual void setTailleElements(sf::Vector2i taille) override{}
		virtual void setRotationElements(int rotation) override{}
		
		//Gestion des textes
		sf::Font police_;
		int tailletexte_;
		std::vector<Choix*> textes_;

		//Gestion des couleurs
		sf::Color couleurSelection_ = sf::Color::Yellow;
		sf::Color couleurInactif_ = sf::Color(100, 100, 100);
		sf::Color couleurActif_ = sf::Color::White;
	};
}

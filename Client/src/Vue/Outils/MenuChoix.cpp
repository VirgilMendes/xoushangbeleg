#pragma once

#include "MenuChoix.h"

namespace Vue
{
	MenuChoix::MenuChoix(std::vector<std::string> textes, sf::Font police, int tailletexte,
	                     sf::Vector2i position): police_(police), tailletexte_(tailletexte)
	{
		for(int i(0); i < textes.size(); i++)
		{
			const std::string texteChoix = textes[i];
			sf::Text texte(texteChoix, police_, tailletexte_);
			texte.setFillColor(couleurActif_);
			texte.move(5, tailletexte_ * i);

			textes_.push_back(new Choix(true, texte));
		}

		position_ = position;
	}

	MenuChoix::~MenuChoix()
	{
		for(Choix* choix : textes_)
		{
			delete choix;
		}
	}

	void MenuChoix::dessinerNode(sf::RenderTarget& target, const sf::Transform& transform)
	{
		for (Choix* choix : textes_)
		{
			target.draw(choix->texte, transform);
		}
	}

	void MenuChoix::setPositionElements(sf::Vector2i position)
	{
		for (int i(0); i < textes_.size(); i++)
		{
			textes_[i]->texte.setPosition(position.x, position.y);
			textes_[i]->texte.move(5, tailletexte_ * i);
		}
	}
}

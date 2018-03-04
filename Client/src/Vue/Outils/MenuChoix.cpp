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

		if (textes_.size() > 0)
		{
			textes_[0]->texte.setFillColor(couleurSelection_);
			iterateur_ = textes_.begin();
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

	void MenuChoix::deplacerAuChoixPrecedant()
	{
		Choix* choix = *iterateur_;
		choix->texte.setFillColor(couleurActif_);
		if (iterateur_ == textes_.begin())
			iterateur_ = --textes_.end();
		else
			--iterateur_;
		choix = *iterateur_;
		const auto iterateurElementSource = iterateur_;
		while (!choix->actif)
		{
			choix = *iterateur_;
			--iterateur_;
			if (iterateur_ == textes_.begin())
				iterateur_ = textes_.end();
			if(iterateur_ == iterateurElementSource)
			{
				choix = *iterateur_;
				break;
			}
		}
		choix->texte.setFillColor(couleurSelection_);
	}

	void MenuChoix::deplacerAuChoixSuivant()
	{
		Choix* choix = *iterateur_;
		choix->texte.setFillColor(couleurActif_);
		++iterateur_;
		if (iterateur_ == textes_.end())
			iterateur_ = textes_.begin();

		choix = *iterateur_;
		const auto iterateurElementSource = iterateur_;
		while (!choix->actif)
		{
			choix = *iterateur_;
			++iterateur_;
			if (iterateur_ == textes_.end())
				iterateur_ = textes_.begin();
			if (iterateur_ == iterateurElementSource)
			{
				choix = *iterateur_;
				break;
			}
		}
		choix->texte.setFillColor(couleurSelection_);
	}

	void MenuChoix::dessinerNode(sf::RenderTarget* target, const sf::Transform& transform)
	{
		for (Choix* choix : textes_)
		{
			target->draw(choix->texte, transform);
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

#pragma once

#include "MenuChoix.h"

Vue::MenuChoix::MenuChoix(std::vector<std::string> textes, sf::Font police, int tailletexte, sf::Vector2i position): textes_(std::vector<Choix>(textes.size())), police_(police), tailletexte_(tailletexte), position_(position)
{
	for(int i(0); i < textes.size(); i++)
	{
		const std::string texteChoix = textes[i];
		sf::Text texte(texteChoix, police_, tailletexte_);
		textes_.push_back(Choix{true, texte});
		texte.setFillColor(couleurActif_);
	}



}


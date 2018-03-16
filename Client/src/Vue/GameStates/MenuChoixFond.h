#pragma once
#include "MenuChoix.h"

namespace Vue
{

	class MenuChoixFond : public MenuChoix
	{
	public:
		MenuChoixFond(std::vector<Controleur::Choix> choix, Controleur::MenuChoix* controleur);
		void MenuChoixFond::afficher();
	private:
		sf::Texture textFond;
		sf::Sprite spriteFond;
	};
}
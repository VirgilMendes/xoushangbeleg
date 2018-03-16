#include "MenuChoixFond.h"
#include"../../Controleur/Navigation.h"
#include "../../Controleur/GameStates/MenuChoix.h"

namespace Vue
{
	MenuChoixFond::MenuChoixFond(std::vector<Controleur::Choix> choix, Controleur::MenuChoix* controleur) : MenuChoix( choix, controleur)
	{
		textFond.loadFromFile("ressources/sprite/fondMenuChoix.png");
		spriteFond.setTexture(textFond);
		spriteFond.setTextureRect(sf::IntRect(0,0,64,64));
		spriteFond.setScale(2.0f, 2.0f);
		spriteFond.setPosition(1280 - 128, 0);
		for (int i(0); i < textes_.size(); i++)
		{
			textes_[i]->setPosition(1150,0);
		}
	}

	void MenuChoixFond::afficher()
	{
		sf::RenderWindow* cible = Controleur::Fenetre::fenetre;
		cible->draw(spriteFond);
		for (sf::Text* texte : textes_)
		{
			cible->draw(*texte);
		}
	}
}
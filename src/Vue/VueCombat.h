#pragma once

#include "Curseur.h"
#include <iostream>
#include "Unite.h"
#include "InfoPersonnageUI.h"
#include "GameState.h"
#include "../Modele/Vecteur2.h"

namespace Vue
{

	class VueCombat : GameState
	{
	public:

		VueCombat(sf::RenderWindow* window);
		~VueCombat();
		
		int run() override;

		void ajouterUnite(std::string nom, std::string cheminTexture, Modele::Vecteur2<int> position);
		void deplacerUnite(std::string nom, Modele::Vecteur2<int> position);

	protected:

		std::map<std::string, sf::Texture*> textures_;

		const int LONGUEUR_GRILLE = 10;
		const int LARGEUR_GRILLE = 10;

		std::vector<std::vector<sf::Sprite>> grille_;

		std::vector<Unite> unites_;
		Curseur curseur_;
		InfoPersonnageUI infoPersonnageUI_;
		sf::Texture textureSol_;
	};

}
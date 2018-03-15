#pragma once
#include <vector>
#include "NouvellePartie.h"
#include "../../Navigation.h"
#include "../../../Vue/GameStates/Menu/NouvellePartie.h"
#include "../Grille.h"

namespace Controleur
{
	NouvellePartie::NouvellePartie() : MenuChoix()
	{
		std::vector<Choix> choix
		{
			{
				"Creer", true, []
				{
					Fenetre::empilerGameState(new Grille(Modele::Vecteur2<int>(32,32)));
				}
			},
			{
				"Nom", true , []
				{
				}
			},
			{
				"Retour", true, []
				{
					Controleur::Fenetre::depilerGameState();
				}
			}
		};
		initialiser(choix, new Vue::NouvellePartie(choix, this));
	}

	NouvellePartie::~NouvellePartie()
	{
	}
}
#pragma once
#include <vector>
#include "RejoindrePartie.h"
#include "../../Navigation.h"
#include "../../../Vue/GameStates/Menu/RejoindrePartie.h"
#include "../Grille.h"
#include "../../Reseaux.h"

namespace Controleur
{
	RejoindrePartie::RejoindrePartie() : MenuChoix()
	{
		std::vector<Choix> choix
		{
			{
				"Rejoindre", true, []
				{
					Reseaux::connecter();
					Fenetre::empilerGameState(new Grille(Modele::Vecteur2<int>(32,32)));
				}
			},
			{
				"IP : ", true , []
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
		initialiser(choix, new Vue::RejoindrePartie(choix, this));
	}

	RejoindrePartie::~RejoindrePartie()
	{
	}
}

#pragma once
#include <vector>
#include "RejoindrePartie.h"
#include "../../Navigation.h"
#include "../../../Vue/GameStates/Menu/RejoindrePartie.h"
#include "../Grille.h"
#include "../MenuCombat/MenuPlacement.h"
#include "../../Reseaux.h"
#include "../../DonneeServeur.h"

namespace Controleur
{
	RejoindrePartie::RejoindrePartie() : MenuChoix()
	{
		std::vector<Choix> choix
		{
			{
				"Rejoindre", true, []
				{
					Reseaux::connecterInvitee();

					std::string xmlGrille = Reseaux::recevoirDonneesBloquant();
					Fenetre::empilerGameState(new Grille(DonneeServeur::initialiserGrilleDepuisChaineXML(xmlGrille)));
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

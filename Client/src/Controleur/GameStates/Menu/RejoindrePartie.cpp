#pragma once
#include <vector>
#include "RejoindrePartie.h"
#include "../../Navigation.h"
#include "../../../Vue/GameStates/Menu/RejoindrePartie.h"
#include "../Grille.h"
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
<<<<<<< Updated upstream
					std::string xmlGrille = Reseaux::recevoirDonneesBloquant();
					Fenetre::empilerGameState(new Grille(DonneeServeur::initialiserGrilleDepuisChaineXML(xmlGrille)));
=======
					Fenetre::empilerGameState(new Grille(Modele::Vecteur2<int>(32,32)));
					Fenetre::empilerGameState(new MenuPlacement(Modele::Equipe::Bleu));
>>>>>>> Stashed changes
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

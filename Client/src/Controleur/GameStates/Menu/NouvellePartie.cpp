#pragma once
#include <vector>
#include "NouvellePartie.h"
#include "../../Navigation.h"
#include "../../../Vue/GameStates/Menu/NouvellePartie.h"

#include "../Grille.h"
#include "../../Reseaux.h"
#include "../../DonneeServeur.h"

namespace Controleur
{
	NouvellePartie::NouvellePartie() : MenuChoix()
	{
		std::vector<Choix> choix
		{
			{
				"Creer", true, []
				{
					Reseaux::connecterHote();
					Fenetre::empilerGameState(new Grille(Modele::Vecteur2<int>(32,32)));

					std::string xmlGrille = DonneeServeur::genererGrilleVersChaineXML(Fenetre::getProchaineGrille()->getGrilleModele());
					Reseaux::envoyerDonneesBloquant(xmlGrille);

					Fenetre::empilerGameState(new MenuPlacement());

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

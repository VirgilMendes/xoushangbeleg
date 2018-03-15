#pragma once
#include "MenuAction.h"
#include "../../Navigation.h"
#include "../Grille.h"

namespace Controleur
{
	MenuAction::MenuAction():MenuChoix()
	{
		std::vector<Choix> choix
		{
			{ 
				"Deplacer", true, []
				{
					Controleur::Grille* grille = Controleur::Fenetre::getProchaineGrille();
					grille->genererCasesAccessiblesDeplacement();
					grille->setEtatCombat(EtatCombat::Deplacement);
					Controleur::Fenetre::depilerGameState();
				}
			},
			{ 
				"Attaquer", true , []
				{
					Controleur::Grille* grille = Controleur::Fenetre::getProchaineGrille();
					grille->genererCasesAccessiblesAttaque();
					grille->setEtatCombat(EtatCombat::Attaque);
					Controleur::Fenetre::depilerGameState();
				}
			},
			{ 
				"Fin du tour", true, []
				{
					Controleur::Grille* grille = Controleur::Fenetre::getProchaineGrille();
					grille->finirTourUniteActuel();
					Controleur::Fenetre::depilerGameState();
				}
			}
		};
		initialiser(choix, new Vue::MenuChoix(choix, this), true);
	}

	MenuAction::~MenuAction()
	{
	}
}

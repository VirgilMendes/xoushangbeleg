#include "MenuPlacement.h" 
#include "../../../Modele/Unite/Unite.h" 
#include "../Grille.h"

namespace Controleur {

	MenuPlacement::MenuPlacement() : MenuChoix()
	{
		std::vector<Choix> choix
		{
			{
				"Tank", true, []
				{
					Controleur::Grille* grille = Controleur::Fenetre::getProchaineGrille();
					grille->setEtatCombat(EtatCombat::Placement);
					grille->setUniteAPlacer(new Modele::Tank(std::to_string(grille->getId()), grille->getEquipeCourante(), Modele::Vecteur2<int>(0, 0)));
					Controleur::Fenetre::depilerGameState();
				}
			},
			{
				"Soldat", true , []
				{
					Controleur::Grille* grille = Controleur::Fenetre::getProchaineGrille();
					grille->setEtatCombat(EtatCombat::Placement);
					grille->setUniteAPlacer(new Modele::Soldat(std::to_string(grille->getId()), grille->getEquipeCourante(), Modele::Vecteur2<int>(0, 0)));
					Controleur::Fenetre::depilerGameState();
				}
			},
			{
				"Archer", true, []
				{
					Controleur::Grille* grille = Controleur::Fenetre::getProchaineGrille();
					grille->setEtatCombat(EtatCombat::Placement);
					grille->setUniteAPlacer(new Modele::Archer(std::to_string(grille->getId()), grille->getEquipeCourante(), Modele::Vecteur2<int>(0, 0)));
					Controleur::Fenetre::depilerGameState();
				}
			}

		};
		initialiser(choix, new Vue::MenuPlacement(choix, this), true);
	}
}

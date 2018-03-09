#pragma once
#include "MenuAction.h"
#include "../../Navigation.h"

namespace Controleur
{
	MenuAction::MenuAction():MenuChoix
	(
		std::vector<Choix>
		{
			{ "Deplacer", true, [] { Controleur::Fenetre::getProchaineGrille()->genererCasesAccessiblesDeplacement(); Controleur::Fenetre::depilerGameState(); } },
			{ "Attaquer", true , [] { Controleur::Fenetre::getProchaineGrille()->genererCasesAccessiblesAttaque(); std::cout << "attaque" << std::endl; Controleur::Fenetre::depilerGameState(); } }
		}
	)
	{

	}

	MenuAction::~MenuAction()
	{
	}
}

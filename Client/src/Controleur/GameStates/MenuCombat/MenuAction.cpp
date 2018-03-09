#pragma once
#include "MenuAction.h"
#include "../../Navigation.h"

namespace Controleur
{
	MenuAction::MenuAction():MenuChoix
	(
		std::vector<Choix>
		{
			{ "Deplacer", true, [] { Controleur::Fenetre::getProchaineGrille()->genererCasesAccessibles(); Controleur::Fenetre::depilerGameState(); } },
			{ "Attaquer", true , [] {std::cout << "attaque" << std::endl; Controleur::Fenetre::depilerGameState(); } }
		}
	)
	{

	}

	MenuAction::~MenuAction()
	{
	}
}

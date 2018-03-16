#pragma once
#include <vector>
#include "MenuPrincipal.h"
#include "../../Navigation.h"
#include "../../../Vue/GameStates/Menu/MenuPrincipal.h"
#include "NouvellePartie.h"
#include "RejoindrePartie.h"

namespace Controleur
{
	MenuPrincipal::MenuPrincipal() :MenuChoix()
	{
		std::vector<Choix> choix
		{
			{
				"Nouveau", true, []
				{
					Fenetre::empilerGameState(new NouvellePartie());
				}
			},
			{
				"Rejoindre", true , []
				{
					Fenetre::empilerGameState(new RejoindrePartie());
				}
			},
			{
				"Charger", true, []
				{
				}
			},
			{
				"Quitter", true, []
				{
					Fenetre::fenetre->close();
				}
			}
		};
		initialiser(choix, new Vue::MenuPrincipal(choix, this));
	}

	MenuPrincipal::~MenuPrincipal()
	{
	}
}

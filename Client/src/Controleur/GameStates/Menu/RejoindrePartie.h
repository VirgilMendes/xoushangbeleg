#pragma once
#include "../MenuChoix.h"
#include "../../../Controleur/GameStates/MenuCombat/MenuPlacement.h"
#include "../../../Modele/Unite/Unite.h"

namespace Controleur
{
	class RejoindrePartie : public MenuChoix
	{
	public:
		RejoindrePartie();
		~RejoindrePartie();
	};
}
#pragma once
#include "../../Modele/Outils/enum.h"
#include <SFML/Graphics.hpp>

namespace Controleur
{

	BETTER_ENUM(ActionDeplacement, int,
		Haut,
		Droite,
		Bas,
		Gauche
	)

	class GameState
	{
	public:

		GameState() {};
		virtual ~GameState() {}

		virtual void handleEvent() = 0;
		virtual void update() = 0;
		virtual void dessiner() = 0;
		
		virtual void enclencherActionDeplacement(const ActionDeplacement& action) {}
		virtual void enclencherActionValidation() {}
		virtual void enclancherActionRetour() {}
		virtual void enclancherActionMenu() {}
		virtual void enclancherActionSpecial() {}
		
		
		virtual bool estInterfaceUtilisateur() { return interfaceUtilisateur; }

	protected:
		bool interfaceUtilisateur = false;
	};
}

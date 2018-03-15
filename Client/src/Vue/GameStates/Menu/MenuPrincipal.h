#pragma once

#include "../../Outils/Jauge.h"
#include <string>
#include "../../Outils/Animation.h"
#include "../../GameStates/GameState.h"
#include "../MenuChoix.h"
#include "../../../Controleur/GameStates/Menu/MenuPrincipal.h"

namespace Vue
{

	class MenuPrincipal : public MenuChoix
	{
	public:

		MenuPrincipal(std::vector<Controleur::Choix> choix, Controleur::MenuPrincipal* controleur);

		void afficher() override;

	private:
		
		sf::Texture textureLogo_;
		sf::Sprite logo_;

		Animation animationLogo_;

	};

}

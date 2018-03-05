#pragma once

#include "../Combat/Curseur.h"
#include <iostream>
#include "../Combat/Unite.h"
#include "../Combat/InterFaceUnite.h"
#include "../../modele/Outils/Vecteur2.h"
#include "../Combat/Grille.h"
#include "../Outils/MenuChoix.h"
#include "../../Modele/Tank.h"
#include "../../Modele/Archer.h"
#include "../Outils/GameState.h"

namespace Vue {

	class Combat : public GameState
	{
	public:

		Combat();
		virtual ~Combat();

		void handleEvent(sf::Event event) override;
		void update() override;
		void draw() override;

	protected:

		Grille grille_;
		MenuChoix* menuAction_;

	};
}

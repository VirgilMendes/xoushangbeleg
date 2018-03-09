#pragma once
#include "GameState.h"
#include "../../Vue/GameStates/PlacementUnite.h"

namespace Controleur {

	class PlacementUnite : public GameState
	{
	public:
		PlacementUnite();

		void handleEvent() override;
		void update() override;
		void afficher() override;



		void deplacerCurseur();
		void setPositionCurseur();


	private:

		Vue::PlacementUnite* vue_;
	};

}
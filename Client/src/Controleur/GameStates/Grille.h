#pragma once 
#include "../../Modele/Grille.h"
#include "GameState.h"
#include "../../Vue/GameStates/Grille.h"

namespace Controleur
{
	class Grille : public GameState
	{
	public:
		Grille(Modele::Vecteur2<int> dimensions_);
		virtual ~Grille();

		void handleEvent() override;
		void update() override;
		void afficher() override;

		void enclencherActionDeplacement(const ActionDeplacement& action) override;
		void enclencherActionValidation() override;
		void enclancherActionRetour() override;
		void enclancherActionMenu() override;
		void enclancherActionSpecial() override;

		void deplacerCurseur(Modele::Vecteur2<int> deplacement);
		void setPositionCurseur(Modele::Vecteur2<int> position);


	private:

		Modele::Grille* modele_;

		Modele::Vecteur2<int> positionCurseur_;

		Vue::Grille* vue_;
	};
}

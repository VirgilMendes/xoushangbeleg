#pragma once
#include <vector>
#include <iostream>
#include "GameState.h"
#include "../../Modele/Outils/Vecteur2.h"
#include <functional>
#include "../../Vue/GameStates/MenuChoix.h"

namespace Controleur
{
	struct Choix
	{
		std::string texte;
		bool actif;
		std::function<void()> fonction;
	};

	class MenuChoix : public GameState
	{
	public:

		MenuChoix(std::vector<Choix> choix);
		~MenuChoix();

		void deplacerAuChoixPrecedant();
		void deplacerAuChoixSuivant();
		void positionnerSurChoix();

		void desactiverChoix(int index);
		void activerChoix(int index);

		void handleEvent() override;
		void update() override;
		void afficher() override;

		void enclencherActionDeplacement(const ActionDeplacement& action) override;
		void enclencherActionValidation() override;
		void enclancherActionRetour() override;
		void enclancherActionMenu() override;
		void enclancherActionSpecial() override;
	
	protected:	

		MenuChoix();
		void initialiser(const std::vector<Choix>& choix, Vue::MenuChoix* vue, const bool interfaceUtilisateur = false);
		
		int choixCourant_;

		Vue::MenuChoix* vue_;
		std::vector<Choix> choix_;
		
	};
}

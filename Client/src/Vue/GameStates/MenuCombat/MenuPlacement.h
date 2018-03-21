#pragma once 
#include "SFML/Graphics.hpp" 
#include "../../Composants/Grille/CurseurPlacement.h"; 
#include "../../../Modele/Unite/Unite.h" 
#include "../MenuChoix.h"
#include "../../../Controleur/GameStates/GameState.h"
#include "../../../Controleur/GameStates/MenuChoix.h"

namespace Controleur
{
	class MenuPlacement;
}

namespace Vue {

	class MenuPlacement : public MenuChoix
	{
	public:
		MenuPlacement(std::vector<Controleur::Choix> choix, Controleur::MenuPlacement* controleur);

		void update() override;
		void afficher() override;

		int getChoix();
		void setChoixCourant(int index) override;
		void changerChoixCourant(int index) override;

		int getNbUniteRestantes();
		void setNbUniteRestantes(int nb);

	private:
		sf::Texture ressource;
		sf::Sprite fond;
		sf::Sprite fondUnitesRestantes;
		sf::Sprite teteTank;
		sf::Sprite teteArcher;
		sf::Sprite teteSoldat;

		sf::Text classeText[3];
		sf::Text textUnitesRestantes;

		int choix_;
		int nbUniteRestantes;

		CurseurPlacement curseur;

		Controleur::MenuPlacement* controleur_;
	};

}

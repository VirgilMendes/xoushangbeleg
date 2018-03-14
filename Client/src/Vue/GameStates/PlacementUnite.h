#pragma once
#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "../Composants/Grille/CurseurPlacement.h";
#include "../../Modele/Unite/Unite.h"

namespace Controleur
{
	class PlacementUnite;
}

namespace Vue {

	class PlacementUnite : public GameState
	{
	public :
		PlacementUnite(Controleur::PlacementUnite* controleur, Modele::Equipe equipe, int nbUniteRestantes);

		

		void handleEvent();
		void update();
		void afficher();

		int getChoix();
		void setChoix(int choix);

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

		int choix;
		int nbUniteRestantes;

		CurseurPlacement curseur;

		Controleur::PlacementUnite* controleur_;
	};

}

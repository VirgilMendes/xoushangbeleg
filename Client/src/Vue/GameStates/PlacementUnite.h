#pragma once
#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "../Composants/Grille/Curseur.h";
#include "../../Modele/Unite/Unite.h"

namespace Vue {

	class PlacementUnite : public GameState
	{
	public :
		PlacementUnite(Modele::Equipe equipe, int nbUniteRestantes);

		void afficher();

		void handleEvent();
		void update();

		int getChoix();
		void setChoix(int choix);

		int getNbUniteRestantes();
		void setNbUniteRestantes(int nb);

	private:
		sf::Texture ressource;
		sf::Sprite fond;
		sf::Sprite teteTank;
		sf::Sprite teteArcher;
		sf::Sprite teteSoldat;

		sf::Text classeText[3];

		int choix;
		int nbUniteRestantes;

		sf::Font font;

		Curseur curseur;
	};

}
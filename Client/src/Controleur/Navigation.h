#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GameStates/GameState.h"
#include <stack>
#include "GameStates/PlacementUnite.h"
#include <pugixml.hpp>
#include <sstream>
#include <list>
#include "../Modele/Grille.h"


namespace Controleur
{
	class Grille;

	class Fenetre
	{
	public:

		Fenetre() = delete;

		static void initialiser();

		static void run();

		static void empilerGameState(GameState* gamestate);
		
		static void depilerGameState();

		static Grille* getProchaineGrille();

		static sf::Font& getPoliceParDefaut();

		static sf::RenderWindow* fenetre;

	private:

		static sf::Font policeParDefaut_;

		static std::list<GameState*> gameStates_;
		static std::list<GameState*> cache_;
	};

	
}

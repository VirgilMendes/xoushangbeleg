#pragma once

#include <pugixml.hpp>
#include <sstream>
#include "GameStates/MenuChoix.h"
#include  "GameStates/Grille.h"
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
#include "Navigation.h"

namespace Controleur {
	class DonneeServeur {
		public :
			static void decodeXml(std::string str);
			static void deplacerUniteDepuisXML(pugi::xml_node root);
			
			static std::string deplacerUnite(std::string nom, Modele::Vecteur2<int> position);
			static std::string GrilleVersChaineXML(Modele::Grille* grille);
			static Modele::Grille* initialiserGrilleDepuisChaineXML(std::string xml);
		private : 
			DonneeServeur() {};
	};
}
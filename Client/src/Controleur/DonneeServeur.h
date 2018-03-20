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
			static void decoderXml(std::string chaineXML);
			
			static std::string genererGrilleVersChaineXML(Modele::Grille* grille);
			static Modele::Grille* initialiserGrilleDepuisChaineXML(std::string xml);

			static std::string genererDeplacementUniteVersXML(std::string nom, Modele::Vecteur2<int> deplacement);
			static void executerDeplacementUniteDepuisXML(pugi::xml_node action);

			static std::string genererAttaqueUniteVersXML(std::string source, std::string cible);
			static void executerAttaqueUniteDepuisXML(pugi::xml_node action);
		
			static std::string genererFinDeTourVersXML();
			static void executerFinDeTourDepuisXML(pugi::xml_node action);
			
		private : 
			DonneeServeur() {};
	};
}
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
		
		static void decodeXml(std::string str) {
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_buffer(str.c_str(), str.length());
			pugi::xml_node root = doc.document_element();
			//verification du premier node
			if ((std::string)root.first_child().name() == "deplacement") 
			{
				deplacerXml(root);
			}
			else if ((std::string)root.first_child().name() == "initialisation") 
			{
				initialiserXml(root);
			}
			else 
			{
				
			}


		}
		static void deplacerXml(pugi::xml_node root) {
			//nom de l'unite
			std::string nomUnite = root.child("deplacement").child("unite").child("nom").child_value();

			Modele::Vecteur2<int> position;
			//position X de l'unite
			position.x = stoi((std::string)root.child("deplacement").child("position").child("x").child_value());
			//position Y de l'unite
			position.y = stoi((std::string)root.child("deplacement").child("position").child("y").child_value());

			//Vue::Combat* Combat = dynamic_cast<Vue::Combat*>(gameStates_.back());
			//Combat->deplacerUnite(nomUnite, position);
		}

		static void initialiserXml(pugi::xml_node root) {
			//Gerer la carte
			//root.child("carte")...

			//Unites
			//Variables pour les unites
			std::string nomUnite;
			Modele::Classe classeUnite;
			Modele::Equipe equipeUnite;
			int vieMaxUnite;
			int vieCouranteUnite;
			int statDefUnite;
			int statAttUnite;
			Modele::Vecteur2<int> positionUnite;

			//Cas a part pour chaque unite
			pugi::xml_node listeUnites = root.child("unites");
			for (pugi::xml_node uniteXml = listeUnites.child("unite"); uniteXml; uniteXml = uniteXml.next_sibling("unite")) {

			}
		}

		static std::string deplacerUnite(std::string nom, Modele::Vecteur2<int> position)
		{
			//vueCombat->deplacerUnite(nom, position);

			pugi::xml_document doc;
			auto root = doc.append_child("paquet");
			pugi::xml_node nodeDeplacement = root.append_child("deplacement");
			pugi::xml_node nodeUnite = nodeDeplacement.append_child("unite");
			pugi::xml_node nodeNom = nodeUnite.append_child("nom");
			nodeNom.text().set(nom.c_str());
			pugi::xml_node nodePosition = nodeDeplacement.append_child("position");
			pugi::xml_node nodeX = nodePosition.append_child("x");
			nodeX.text().set((std::to_string(position.x).c_str()));
			pugi::xml_node nodeY = nodePosition.append_child("y");
			nodeY.text().set(std::to_string(position.y).c_str());
			std::stringstream flux;
			doc.print(flux);
			return flux.str();
		}
		std::string initialisatonCarteUnite() {
			pugi::xml_document doc;
			auto root = doc.append_child("paquet");
			pugi::xml_node nodeCarte = root.append_child("carte");
			pugi::xml_node nodeNomCarte = nodeCarte.append_child("nom");
			pugi::xml_node nodeListeUnite = root.append_child("unites");
			pugi::xml_node nodeUnite;
			pugi::xml_node nodeNomUnite;
			pugi::xml_node nodeClasseUnite;
			pugi::xml_node nodeEquipeUnite;
			pugi::xml_node nodeVieMaxUnite;
			pugi::xml_node nodeVieCouranteUnite;
			pugi::xml_node nodeAttaqueUnite;
			pugi::xml_node nodeDefenseUnite;
			pugi::xml_node nodePositionUnite;
			pugi::xml_node nodePositionXUnite;
			pugi::xml_node nodePositionYUnite;
			Modele::Vecteur2<int> position;
			std::set<Modele::Unite> listeUnite_;
			//utiliser listeUnite de Carte.h{
			for (auto iterateur(listeUnite_.begin()); iterateur != listeUnite_.end(); iterateur++){
				Modele::Unite unite = *iterateur;
				position = unite.getPosition();

				nodeUnite = nodeListeUnite.append_child("unite");

				nodeNomUnite = nodeUnite.append_child("nomunite");
				nodeNomUnite.text().set(unite.getNom().c_str());

				nodeClasseUnite = nodeUnite.append_child("classe");
				nodeClasseUnite.text().set(unite.getClasse()._to_string());

				nodeEquipeUnite = nodeUnite.append_child("equipe");
				nodeEquipeUnite.text().set(unite.getEquipe()._to_string());

				nodeVieMaxUnite = nodeUnite.append_child("vieMax");
				nodeVieMaxUnite.text().set(unite.getVieMax());

				nodeVieCouranteUnite = nodeUnite.append_child("vieCourante");
				nodeVieCouranteUnite.text().set(unite.getVieCourante());

				nodeAttaqueUnite = nodeUnite.append_child("attaque");
				nodeAttaqueUnite.text().set(unite.getAttaque());

				nodeDefenseUnite = nodeUnite.append_child("defense");
				nodeDefenseUnite.text().set(unite.getDefense());

				nodePositionUnite = nodeUnite.append_child("position");

				nodePositionXUnite = nodePositionUnite.append_child("x");
				nodePositionXUnite.text().set(position.x);

				nodePositionYUnite = nodePositionUnite.append_child("x");
				nodePositionYUnite.text().set(position.y);
			}
			std::stringstream flux;
			doc.print(flux);
			return flux.str();
		}

		static sf::RenderWindow* fenetre;

	private:

		static sf::Font policeParDefaut_;

		static std::list<GameState*> gameStates_;
		static std::list<GameState*> cache_;
	};

	
}

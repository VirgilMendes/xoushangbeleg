#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Vue/GameStates/GameState.h"
#include <stack>
#include "../Vue/GameStates/VueCombat.h"
#include <pugixml.hpp>
#include <sstream>

namespace Controleur
{
	class Fenetre : public sf::RenderWindow
	{
	public:
		Fenetre() : RenderWindow(sf::VideoMode(1000, 700), "Xoushangbeleg")
		{
			setFramerateLimit(60);
			Vue::VueCombat* vueCombat = new Vue::VueCombat(this);
			gameStates_.push(vueCombat);
			vueCombat->deplacerUnite("Archer1", sf::Vector2i(10, 7));
		}

		void run()
		{
			while (isOpen())
			{
				gameStates_.top()->run();
			}
		}

		void ajouterGameState(Vue::GameState* gamestate)
		{
			gameStates_.push(gamestate);
		}
		
		void decodeXml(std::string str) {
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_buffer(str.c_str(), str.length());
			pugi::xml_node root = doc.document_element();
			//verification du premier node
			if ((std::string)root.first_child().name() == "deplacement") 
			{
				//nom de l'unite
				std::string nomUnite = root.child("deplacement").child("unite").child("nom").child_value();

				Modele::Vecteur2<int> position;
				//position X de l'unite
				position.x = stoi((std::string)root.child("deplacement").child("position").child("x").child_value());
				//position Y de l'unite
				position.y = stoi((std::string)root.child("deplacement").child("position").child("y").child_value());
				
				Vue::VueCombat* vueCombat = dynamic_cast<Vue::VueCombat*>(gameStates_.top());
				vueCombat->deplacerUnite(nomUnite, position);
			}
			else if ((std::string)root.first_child().name() == "carte") 
			{
				
			}
			else 
			{
				
			}


		}

		std::string deplacerUnite(std::string nom, Modele::Vecteur2<int> position)
		{
			Vue::VueCombat* vueCombat = dynamic_cast<Vue::VueCombat*>(gameStates_.top());
			vueCombat->deplacerUnite(nom, position);

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

	private:

		std::stack<Vue::GameState*> gameStates_;
	};
}

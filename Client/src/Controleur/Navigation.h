#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Vue/GameStates/GameState.h"
#include <stack>
#include "../Vue/GameStates/VueCombat.h"
#include <pugixml.hpp>

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
			if ((std::string)root.first_child().name() == "deplacement") {
				//nom de l'unite
				std::string uniteName = root.child("deplacement").child("unite").child("nom").child_value();
				//position X de l'unite
				int posX = stoi((std::string)root.child("deplacement").child("position").child("x").child_value());
				//position Y de l'unite
				int posY = stoi((std::string)root.child("deplacement").child("position").child("y").child_value());
				//unite.setPosition(Modele::Vecteur2<int>(posX, posY)
			}
			else if ((std::string)root.first_child().name() == "carte") {
				//a completer
			}
			else {
				//au cas ou
			}


		}

	private:

		std::stack<Vue::GameState*> gameStates_;
	};
}

#pragma once
#include <SFML/Graphics.hpp>

namespace Controleur
{
	class Fenetre;
}

namespace Vue
{

	class GameState
	{
	public:

		GameState() {};
		virtual void handleEvent(sf::Event event) = 0;
		virtual void update() = 0;
		virtual void draw() = 0;
		virtual bool estInterfaceUtilisateur() { return interfaceUtilisateur; }

	protected:
		bool interfaceUtilisateur = false;

	};
}

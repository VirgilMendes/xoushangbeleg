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

		GameState(Controleur::Fenetre* fenetre) : fenetre_(fenetre) {};
		virtual int run() = 0;

	protected:
		Controleur::Fenetre* fenetre_;
	};
}

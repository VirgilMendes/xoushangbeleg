#pragma once
#include "../../Modele/Outils/enum.h"
#include <SFML/Graphics.hpp>
#include "../Constante.h"

namespace Vue
{

	class GameState
	{
	public:

		GameState() {};
		virtual ~GameState() {}

		virtual void handleEvent() = 0;
		virtual void update() = 0;
		virtual void dessiner() = 0;
	};
}

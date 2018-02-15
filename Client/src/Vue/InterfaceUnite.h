#pragma once

#include "SFML/Graphics.hpp"
#pragma once

#include <string>
#include "../Modele/Unite.h"
#include "../Modele/Archer.h"
#include "../Modele/Soldat.h"
#include "../Modele/Tank.h"

#include "Jauge.h"

namespace Vue
{

	class InterfaceUnite : public sf::Drawable
	{
	public:
		InterfaceUnite::InterfaceUnite(Modele::Unite unite);



	private:
		Modele::Unite unite;

		//Jauge barrevie;
		sf::RectangleShape fond;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};


}
#pragma once
#include "../../Modele/Outils/Vecteur2.h"
#include "SFML/Graphics.hpp"
#include <list>

namespace Vue
{
	class FiltreCase
	{
	public:
		FiltreCase(std::list<Modele::Vecteur2<int>> cases);
		~FiltreCase();

		void dessiner(sf::RenderWindow* cible, sf::RenderStates& etat);

	private:

		sf::Image image_;
		sf::Texture* texture_;
		sf::VertexArray sommets_;


	};
}

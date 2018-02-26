#pragma once 
#include "SFML/Graphics.hpp"
#include "../../Modele/Carte.h"
#include "../../Modele/Case.h"

namespace Vue
{
	typedef std::pair<Modele::Terrain, int > parametreSol;
	typedef std::tuple<Modele::Terrain, Modele::Obstacle, int > parametreElement;

	class CarteGUI : public sf::Drawable, public sf::Transformable
	{
		public :
			CarteGUI();

		private :

			Modele::Carte carte;

			sf::Texture map;

			sf::VertexArray tabVertex;

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}
#pragma once 
#include "SFML/Graphics.hpp"
#include "../../Modele/Grille.h"

namespace Vue
{
	typedef std::pair<Modele::Terrain, int > parametreSol;
	typedef std::tuple<Modele::Terrain, Modele::Obstacle, int > parametreElement;

	class Grille : public sf::Drawable, public sf::Transformable
	{
		public :
			Grille();

		private :

			Modele::Grille grille_;

			sf::Texture map;

			sf::VertexArray tabVertex;

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}
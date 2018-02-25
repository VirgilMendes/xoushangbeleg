#pragma once
#include "SFML/Graphics.hpp"
#include "../../Modele/Carte.h"
#include "../../Modele/Case.h"

namespace Vue
{
	typedef std::pair<Modele::Terrain, int > parametreSol;
	typedef std::tuple<Modele::Terrain, Modele::Obstacle, int > parametreElement;

	class CarteGUI : public sf::Drawable
	{
		public :
			CarteGUI();

		private :

			Modele::Carte carte;

			sf::Texture carteFond;
			sf::Texture carteObstacle;

			sf::Sprite carteSol;
			sf::Sprite carteElement ;

			std::map<parametreSol, sf::IntRect> sol;
			std::map<parametreElement, sf::IntRect> element;

			sf::Sprite carteADessiner[32][32];

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}
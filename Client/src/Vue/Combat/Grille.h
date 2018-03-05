#pragma once 
#include "SFML/Graphics.hpp"
#include "../../Modele/Grille.h"
#include "../Outils/Node.h"
#include "Curseur.h"

namespace Vue
{
	typedef std::pair<Modele::Terrain, int > ParametreSol;
	typedef std::tuple<Modele::Terrain, Modele::Obstacle, int > ParametreElement;

	class Grille : public sf::View, Node
	{
	public :
		Grille(Modele::Grille* grille);
		virtual ~Grille() { delete grille_; }

		void setPositionCurseur(Modele::Vecteur2<int> position);
		void deplacerCurseur(Modele::Vecteur2<int> deplacement);

		void dessiner(sf::RenderTarget& target, sf::RenderStates states);

	protected:
		void dessinerNode(sf::RenderTarget* target, const sf::Transform& transform) override{}
		void setPositionElements(sf::Vector2i position) override {}
		void setTailleElements(sf::Vector2i taille) override {}
		void setRotationElements(int rotation) override {}

		private :

			Curseur curseur_;

			Modele::Grille* grille_;

			sf::Texture textureGrille_;
			sf::Texture textureObstacle_;

			sf::VertexArray sommets_;
	};
}

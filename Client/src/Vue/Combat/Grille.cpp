#include "Grille.h"
#include "../../Modele/Case.h"

#define RESOLUTION 64

namespace Vue
{
	Grille::Grille(Modele::Grille* grille) : grille_(grille)
	{

		if (!textureGrille_.loadFromFile("ressources/sprite/map.png"))
		{
			std::cout << "erreur chargement Texture TextureGrille.png" << std::endl;
		}
		if (!textureObstacle_.loadFromFile("ressources/sprite/TextureObstacles.png"))
		{
			std::cout << "erreur chargement Texture TextureObstacle.png" << std::endl;
		}

		const int largeur(grille_->getDimension().x), hauteur(grille_->getDimension().y);

		// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
		sommets_.setPrimitiveType(sf::Quads);
		sommets_.resize( largeur * hauteur * 4);

		// on remplit le tableau de vertex, avec un quad par tuile
		for (unsigned int i = 0; i < largeur; ++i)
			for (unsigned int j = 0; j < hauteur; ++j)
			{
				Modele::Case* caseGrille = grille_->getCase(Modele::Vecteur2<int>(i,j));

				// on récupère le code de tuile courant
				const int caseNombre(caseGrille->getTerrain()._to_integral() * 8 + caseGrille->getObstacle()._to_integral() * 2 + 1);

				// on récupère un pointeur vers le quad à définir dans le tableau de vertex
				sf::Vertex* quad = &sommets_[(i + j * largeur) * 4];

				// on définit ses quatre coins
				quad[0].position = sf::Vector2f(i * RESOLUTION, j * RESOLUTION);
				quad[1].position = sf::Vector2f((i + 1) * RESOLUTION, j * RESOLUTION);
				quad[2].position = sf::Vector2f((i + 1) * RESOLUTION, (j + 1) * RESOLUTION);
				quad[3].position = sf::Vector2f(i * RESOLUTION, (j + 1) * RESOLUTION);

				// on définit ses quatre coordonnées de texture
				quad[0].texCoords = sf::Vector2f(caseNombre * RESOLUTION, 0);
				quad[1].texCoords = sf::Vector2f((caseNombre + 1) * RESOLUTION, 0);
				quad[2].texCoords = sf::Vector2f((caseNombre + 1) * RESOLUTION, RESOLUTION);
				quad[3].texCoords = sf::Vector2f(caseNombre * RESOLUTION, RESOLUTION);
			}
		setCenter(0, 0);
	}

	void Grille::setPositionCurseur(Modele::Vecteur2<int> position)
	{
		curseur_.setPosition(position);
		setCenter(position.x*64, position.y*64);
	}

	void Grille::deplacerCurseur(Modele::Vecteur2<int> deplacement)
	{
		curseur_.deplacerCurseur(deplacement);
		setCenter(getCenter()+sf::Vector2f(deplacement.x*64, deplacement.y*64));
	}

	void Grille::dessiner(sf::RenderTarget& target, sf::RenderStates states)
	{
		target.setView(*this);
		// on applique la texture du tileset du sol
		states.texture = &textureGrille_;

		// et on dessine enfin le tableau de vertex du sol 
		target.draw(sommets_, states);

		target.draw(curseur_);

		target.setView(target.getDefaultView());
	}
}
#include "CarteGUI.h"
#include "../../Modele/Case.h"
#include "../../Modele/Carte.h"

namespace Vue
{
	CarteGUI::CarteGUI() 
	{
		int largeur = 32 , hauteur = 32;

		if (!map.loadFromFile("ressources/sprite/map.png"))
		{
			std::cout << "erreur chargement Texture map.png" << std::endl;
		}


		// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
		tabVertex.setPrimitiveType(sf::Quads);
		tabVertex.resize(largeur * hauteur * 4);

		int tileNumber = 0;
		Modele::Case caseTemp;

		// on remplit le tableau de vertex, avec un quad par tuile
		for (unsigned int i = 0; i < largeur; ++i)
			for (unsigned int j = 0; j < hauteur; ++j)
			{
				caseTemp = carte.getCase(i, j);


				// on récupère le code de tuile courant
				switch (caseTemp.getTerrain())
				{
				case Modele::Terrain::herbeux :
					tileNumber = 0;
					break;
				case Modele::Terrain::sableux:
					tileNumber = 8;
					break;
				case Modele::Terrain::aquatique:
					tileNumber = 16;
					break;
				case Modele::Terrain::rocheux:
					tileNumber = 24;
					break;
				}

				switch (caseTemp.getObstacle())
				{
				case Modele::Obstacle::aucun:
					tileNumber = tileNumber + 1;
					break;
				case Modele::Obstacle::arbre:
					tileNumber = tileNumber + 3;
					break;
				case Modele::Obstacle::buisson:
					tileNumber = tileNumber + 5;
					break;
				case Modele::Obstacle::rocher:
					tileNumber = tileNumber + 7;
					break;
				}

				// on récupère un pointeur vers le quad à définir dans le tableau de vertex
				sf::Vertex* quad = &tabVertex[(i + j * largeur) * 4];

				// on définit ses quatre coins
				quad[0].position = sf::Vector2f(i * 64, j * 64);
				quad[1].position = sf::Vector2f((i + 1) * 64, j * 64);
				quad[2].position = sf::Vector2f((i + 1) * 64, (j + 1) * 64);
				quad[3].position = sf::Vector2f(i * 64, (j + 1) * 64);

				// on définit ses quatre coordonnées de texture
				quad[0].texCoords = sf::Vector2f(tileNumber * 64, 0);
				quad[1].texCoords = sf::Vector2f((tileNumber + 1) * 64, 0);
				quad[2].texCoords = sf::Vector2f((tileNumber + 1) * 64, 64);
				quad[3].texCoords = sf::Vector2f(tileNumber * 64, 64);
			}
	}

	void CarteGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// on applique la transformation du sol
		states.transform *= getTransform();

		// on applique la texture du tileset du sol
		states.texture = &map;

		// et on dessine enfin le tableau de vertex du sol 
		target.draw(tabVertex, states);

	}
}
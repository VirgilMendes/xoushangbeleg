#include "CarteGUI.h"
#include "../../Modele/Carte.h"

namespace Vue
{
	CarteGUI::CarteGUI() : sf::Drawable()
	{
		frame = 1;

		if (!carteFond.loadFromFile("ressources/sprite/mapFond.png"))
		{
			std::cout << "erreur chargement Texture mapFond.png" << std::endl;
		}
		

		if (!carteObstacle.loadFromFile("ressources/sprite/mapObstacles.png"))
		{
			std::cout << "erreur chargement Texture mapObstacles.png" << std::endl;
		}

		
		sol[parametreSol(Modele::Terrain::herbeux, 1 )] = sf::IntRect(0, 0, 32, 32);
		sol[parametreSol(Modele::Terrain::herbeux, 2)] = sf::IntRect(32, 0, 32, 32);
		sol[parametreSol(Modele::Terrain::sableux, 1)] = sf::IntRect(0, 32, 32, 32);
		sol[parametreSol(Modele::Terrain::sableux, 2)] = sf::IntRect(32, 32, 32, 32);
		sol[parametreSol(Modele::Terrain::aquatique, 1)] = sf::IntRect(0, 64, 32, 32);
		sol[parametreSol(Modele::Terrain::aquatique, 2)] = sf::IntRect(32, 64, 32, 32);
		sol[parametreSol(Modele::Terrain::rocheux, 1)] = sf::IntRect(0, 96, 32, 32);
		sol[parametreSol(Modele::Terrain::rocheux, 2)] = sf::IntRect(32, 96, 32, 32);

		
		element[parametreElement(Modele::Terrain::herbeux, Modele::Obstacle::arbre, 1)] = sf::IntRect(0, 0, 32, 32);
		element[parametreElement(Modele::Terrain::herbeux, Modele::Obstacle::arbre, 2)] = sf::IntRect(32, 0, 32, 32);
		element[parametreElement(Modele::Terrain::herbeux, Modele::Obstacle::buisson, 1)] = sf::IntRect(64, 0, 32, 32);
		element[parametreElement(Modele::Terrain::herbeux, Modele::Obstacle::buisson, 2)] = sf::IntRect(96, 0, 32, 32);
		element[parametreElement(Modele::Terrain::herbeux, Modele::Obstacle::rocher, 1)] = sf::IntRect(128, 0, 32, 32);
		element[parametreElement(Modele::Terrain::herbeux, Modele::Obstacle::rocher, 2)] = sf::IntRect(160, 0, 32, 32);

		element[parametreElement(Modele::Terrain::sableux, Modele::Obstacle::arbre, 1)] = sf::IntRect(0, 32, 32, 32);
		element[parametreElement(Modele::Terrain::sableux, Modele::Obstacle::arbre, 2)] = sf::IntRect(32, 32, 32, 32);
		element[parametreElement(Modele::Terrain::sableux, Modele::Obstacle::buisson, 1)] = sf::IntRect(64, 32, 32, 32);
		element[parametreElement(Modele::Terrain::sableux, Modele::Obstacle::buisson, 2)] = sf::IntRect(96, 32, 32, 32);
		element[parametreElement(Modele::Terrain::sableux, Modele::Obstacle::rocher, 1)] = sf::IntRect(128, 32, 32, 32);
		element[parametreElement(Modele::Terrain::sableux, Modele::Obstacle::rocher, 2)] = sf::IntRect(160, 32, 32, 32);

		element[parametreElement(Modele::Terrain::aquatique, Modele::Obstacle::arbre, 1)] = sf::IntRect(0, 64, 32, 32);
		element[parametreElement(Modele::Terrain::aquatique, Modele::Obstacle::arbre, 2)] = sf::IntRect(32, 64, 32, 32);
		element[parametreElement(Modele::Terrain::aquatique, Modele::Obstacle::buisson, 1)] = sf::IntRect(64, 64, 32, 32);
		element[parametreElement(Modele::Terrain::aquatique, Modele::Obstacle::buisson, 2)] = sf::IntRect(96, 64, 32, 32);
		element[parametreElement(Modele::Terrain::aquatique, Modele::Obstacle::rocher, 1)] = sf::IntRect(128, 64, 32, 32);
		element[parametreElement(Modele::Terrain::aquatique, Modele::Obstacle::rocher, 2)] = sf::IntRect(160, 64, 32, 32);

		element[parametreElement(Modele::Terrain::rocheux, Modele::Obstacle::arbre, 1)] = sf::IntRect(0, 96, 32, 32);
		element[parametreElement(Modele::Terrain::rocheux, Modele::Obstacle::arbre, 2)] = sf::IntRect(32, 96, 32, 32);
		element[parametreElement(Modele::Terrain::rocheux, Modele::Obstacle::buisson, 1)] = sf::IntRect(64, 96, 32, 32);
		element[parametreElement(Modele::Terrain::rocheux, Modele::Obstacle::buisson, 2)] = sf::IntRect(96, 96, 32, 32);
		element[parametreElement(Modele::Terrain::rocheux, Modele::Obstacle::rocher, 1)] = sf::IntRect(128, 96, 32, 32);
		element[parametreElement(Modele::Terrain::rocheux, Modele::Obstacle::rocher, 2)] = sf::IntRect(160, 96, 32, 32);

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; i++)
			{
				carteSol[i][j].setTexture(carteFond);
				carteSol[i][j].setTextureRect(sol[parametreSol(carte.getCase(i,j).getTerrain(), frame)]);
				carteSol[i][j].setPosition(i * 32, j * 32);
				carteElement[i][j].setTexture(carteObstacle);
				carteElement[i][j].setTextureRect(element[parametreElement(carte.getCase(i, j).getTerrain(), carte.getCase(i, j).getObstacle(), frame)]);
				carteElement[i][j].setPosition(i * 32, j * 32);
			}
		}
	}

	void CarteGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; i++)
			{
				target.draw(carteSol[i][j], states);
				target.draw(carteElement[i][j], states);
			}
		}
	}
}
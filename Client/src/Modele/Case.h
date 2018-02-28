#pragma once
#include <iostream>
#include <string>
#include "Unite.h"
#include "Outils/enum.h"

namespace Modele
{
	BETTER_ENUM( Terrain, int, 
		herbeux,
		sableux,
		aquatique,
		rocheux
	)

	BETTER_ENUM( Obstacle, int,
		aucun,
		arbre,
		buisson,
		rocher
	)

	class Case
	{
	public :

		Case();
		Case(Unite* unite, Terrain terrain, Obstacle obstacle);

		Unite* getUnite();
		void setUnite( Unite* unite);

		Terrain getTerrain();
		void setTerrain(Terrain terrain);

		Obstacle getObstacle();
		void setObstacle(Obstacle obstacle);

	private :

		Unite* unite;
		Terrain terrain;
		Obstacle obstacle;

	};

}

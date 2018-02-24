#pragma once
#include <iostream>
#include <string>
#include "Unite.h"

namespace Modele
{
	enum class Terrain
	{
		herbeux,
		sableux,
		aquatique,
		rocheux
	};

	enum class Obstacle
	{
		aucun,
		arbre,
		buisson,
		rocher
	};

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
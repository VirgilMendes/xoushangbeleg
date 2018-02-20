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



	private :

		Unite* unite;

	};

}
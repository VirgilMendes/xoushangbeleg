//_CRT_SECURE_NO_WARNINGS
#include "Carte.h";
#include <stdio.h>
#include <stdlib.h>

namespace Modele
{
	Carte::Carte()
	{
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				carte[i][j] = Case(nullptr, Terrain::herbeux, Obstacle::aucun);
			}
		}
		carte[0][0] = Case(nullptr, Terrain::aquatique, Obstacle::rocher);
	}

	Case Carte::getCase(int x, int y)
	{
		return this->carte[x][y];
	}

}
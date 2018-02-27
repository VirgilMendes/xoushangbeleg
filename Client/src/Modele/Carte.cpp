//_CRT_SECURE_NO_WARNINGS
#include "Carte.h";
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector> 

namespace Modele
{
	Carte::Carte()
	{
		srand((unsigned) time(NULL));

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				carte[i][j] = Case(nullptr, Terrain::herbeux, Obstacle::aucun);
			}
		}

		// génération de l'eau
		this->genererEau();

		// génération du sable autour de l'eau
		this->genererPlage();
	}

	void Carte::genererEau() 
	{
		int nbCaseAquatique = 0;
		

		int testRandi;
		int testRandj;

		testRandi = rand() % 32;
		testRandj = rand() % 32;
		
		carte[testRandi][testRandj] = Case(nullptr, Terrain::aquatique, Obstacle::aucun);
		tabAquatique.push_back(Vecteur2<int>(testRandi, testRandj));

		int nbEssais = 0;
		int testRandAquatique;
		if (tabAquatique.size() != 0)
		{
			while (nbCaseAquatique < 100 && nbEssais < 1000)
			{
				testRandAquatique = rand() % tabAquatique.size();

				for (int i = tabAquatique[testRandAquatique].x - 1; i <= tabAquatique[testRandAquatique].x + 1; i++)
				{
					for (int j = tabAquatique[testRandAquatique].y - 1; j <= tabAquatique[testRandAquatique].y + 1; j++)
					{
						if (i < 32 && j < 32 && i >= 0 && j >= 0)
						{
							if (carte[i][j].getTerrain() == Terrain::herbeux)
							{
								carte[i][j].setTerrain(Terrain::aquatique);
								tabAquatique.push_back(Vecteur2<int>(i, j));
								nbCaseAquatique = nbCaseAquatique + 1;
							}
						}
						nbEssais = nbEssais + 1;
					}
				}
			}
		}
	}

	void Carte::genererPlage()
	{
		int tailleVoisinageEau;
		for (int y = 0; y < tabAquatique.size(); y++)
		{
			tailleVoisinageEau = rand() % 4 + 1;
			std::cout << " rand = "<< tailleVoisinageEau << std::endl;
			for (int i = tabAquatique[y].x - tailleVoisinageEau; i <= tabAquatique[y].x + tailleVoisinageEau; i++)
			{
				if (i < 32 && tabAquatique[y].y < 32 && i >= 0 && tabAquatique[y].y >= 0)
				{
					if (carte[i][tabAquatique[y].y].getTerrain() == Terrain::herbeux)
					{
						carte[i][tabAquatique[y].y].setTerrain(Terrain::sableux);
					}
				}
			}
			for (int j = tabAquatique[y].y - tailleVoisinageEau; j <= tabAquatique[y].y + tailleVoisinageEau; j++)
			{
				if (tabAquatique[y].x < 32 && j < 32 && tabAquatique[y].x >= 0 && j >= 0)
				{
					if (carte[tabAquatique[y].x][j].getTerrain() == Terrain::herbeux)
					{
						carte[tabAquatique[y].x][j].setTerrain(Terrain::sableux);
					}
				}
			}
		}
	}

	Case Carte::getCase(int x, int y)
	{
		return carte[x][y];
	}



}
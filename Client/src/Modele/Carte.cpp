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
		this->genererEau(100);

		// génération du sable autour de l'eau
		this->genererPlage(5);

		// génération du terrain rocheux
		this->genererRocheux(50, 5);

		this->genererObstacles();
	}

	void Carte::genererEau( int tailleMax) 
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
			while (nbCaseAquatique < tailleMax && nbEssais < 1000)
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

	void Carte::genererPlage( int circonferenceMax)
	{
		int tailleVoisinageEau;
		int i = 0;
		int j = 0;
		for (int y = 0; y < tabAquatique.size(); y++)
		{
			tailleVoisinageEau = rand() % circonferenceMax + 1;
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
			i = 0 + tailleVoisinageEau;
			j = 0 - tailleVoisinageEau;
			while ( j <= tailleVoisinageEau && i >= (-1)*tailleVoisinageEau)
			{
				if (carte[tabAquatique[y].x + i][tabAquatique[y].y + j].getTerrain() == Terrain::herbeux  && tabAquatique[y].x + i < 32 && tabAquatique[y].x + i >= 0 && tabAquatique[y].y + j < 32 && tabAquatique[y].y + j >= 0)
				{
					carte[tabAquatique[y].x + i][tabAquatique[y].y + j].setTerrain(Terrain::sableux);
				}
				i = i - 1;
				j = j + 1;
			}
			i = 0 - tailleVoisinageEau;
			while ( i <= tailleVoisinageEau)
			{
				if (carte[tabAquatique[y].x + i][tabAquatique[y].y + i].getTerrain() == Terrain::herbeux && tabAquatique[y].x + i < 32 && tabAquatique[y].x + i >= 0 && tabAquatique[y].y + i < 32 && tabAquatique[y].y + i >= 0)
				{
					carte[tabAquatique[y].x + i][tabAquatique[y].y + i].setTerrain(Terrain::sableux);
				}
				i = i + 1;
			}
		}
	}

	void Carte::genererRocheux(int taille, int epaisseur)
	{
		int i;
		int j;
		int choixCote;
		choixCote = rand() % 4;
		switch (choixCote)
		{
		case 0:
			i = 0;
			j = 0;
			while ( j < 32 )
			{
				if (carte[i][j].getTerrain() == Terrain::aquatique)
				{
					std::cout << " eau trouvée en : i = "<<i<<" / j = "<<j << std::endl;
					i = 31;
					j = 100;
				}
				j++;
			}
			j = rand() % 32;
			break;
		case 1:
			i = 31;
			j = 0;
			while (j < 32)
			{
				if (carte[i][j].getTerrain() == Terrain::aquatique)
				{
					std::cout << " eau trouvée en : i = " << i << " / j = " << j << std::endl;
					i = 0;
					j = 100;
				}
				j++;
			}
			j = rand() % 32;
			break;
		case 2:
			j = 0;
			i = 0;
			while (i < 32)
			{
				if (carte[i][j].getTerrain() == Terrain::aquatique)
				{
					std::cout << " eau trouvée en : i = " << i << " / j = " << j <<std::endl;
					j = 31;
					i = 100;
				}
				i++;
			}
			i = rand() % 32;
			break;
		case 3:
			j = 31;
			i = 0;
			while (i < 32)
			{
				if (carte[i][j].getTerrain() == Terrain::aquatique)
				{
					std::cout << " eau trouvée en : i = " << i << " / j = " << j << std::endl;
					j = 0;
					i = 100;
				}
				i++;
			}
			i = rand() % 32;
			break;
		}
		std::cout << " base : i = " << i << " / j = " << j;
		carte[i][j].setTerrain(Terrain::rocheux);
		tabRocheux.push_back(Vecteur2<int>(i, j));
		int essais = 0;
		while (tabRocheux.size() < taille && essais < 3000)
		{
			choixCote = rand() % 4;
			switch (choixCote)
			{
			case 0:
				if (tabRocheux[tabRocheux.size() - 1].x - 1 >= 0 && tabRocheux[tabRocheux.size() - 1].x - 1 < 32 && tabRocheux[tabRocheux.size() - 1].y < 32 && tabRocheux[tabRocheux.size() - 1].y >= 0)
				{
					if (carte[tabRocheux[tabRocheux.size() - 1].x - 1][tabRocheux[tabRocheux.size() - 1].y].getTerrain() != Terrain::aquatique && carte[tabRocheux[tabRocheux.size() - 1].x - 1][tabRocheux[tabRocheux.size() - 1].y].getTerrain() != Terrain::rocheux)
					{
						carte[tabRocheux[tabRocheux.size() - 1].x - 1][tabRocheux[tabRocheux.size() - 1].y].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x - 1, tabRocheux[tabRocheux.size() - 1].y));
					}
				}
				break;
			case 1:
				if (tabRocheux[tabRocheux.size() - 1].x + 1 >= 0 && tabRocheux[tabRocheux.size() - 1].x + 1 < 32 && tabRocheux[tabRocheux.size() - 1].y < 32 && tabRocheux[tabRocheux.size() - 1].y >= 0)
				{
					if (carte[tabRocheux[tabRocheux.size() - 1].x + 1][tabRocheux[tabRocheux.size() - 1].y].getTerrain() != Terrain::aquatique && carte[tabRocheux[tabRocheux.size() - 1].x + 1][tabRocheux[tabRocheux.size() - 1].y].getTerrain() != Terrain::rocheux)
					{
						carte[tabRocheux[tabRocheux.size() - 1].x + 1][tabRocheux[tabRocheux.size() - 1].y].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x + 1, tabRocheux[tabRocheux.size() - 1].y));
					}
				}
				break;
			case 2:
				if (tabRocheux[tabRocheux.size() - 1].x >= 0 && tabRocheux[tabRocheux.size() - 1].x < 32 && tabRocheux[tabRocheux.size() - 1].y - 1 < 32 && tabRocheux[tabRocheux.size() - 1].y - 1 >= 0)
				{
					if (carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y - 1].getTerrain() != Terrain::aquatique && carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y - 1].getTerrain() != Terrain::rocheux)
					{
						carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y - 1].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x, tabRocheux[tabRocheux.size() - 1].y - 1));
					}
				}
				break;
			case 3:
				if (tabRocheux[tabRocheux.size() - 1].x >= 0 && tabRocheux[tabRocheux.size() - 1].x < 32  && tabRocheux[tabRocheux.size() - 1].y + 1 < 32 && tabRocheux[tabRocheux.size() - 1].y + 1 >= 0)
				{
					if (carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y + 1].getTerrain() != Terrain::aquatique && carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y + 1].getTerrain() != Terrain::rocheux)
					{
						carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y + 1].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x, tabRocheux[tabRocheux.size() - 1].y + 1));
					}
				}
				break;
			}
			essais++;
		}
		std::cout << "	nombre essais = " << essais << "  /  taille = " << tabRocheux.size() << std::endl;

		for (int e = 0; e < tabRocheux.size(); e++) // on va effectuer un traitement sur tout le chemin de "rocheux" fait precedemment
		{
			for (int a = tabRocheux[e].x - epaisseur; a < tabRocheux[e].x + epaisseur ; a++)
			{
				for (int b = tabRocheux[e].y - epaisseur; b < tabRocheux[e].y + epaisseur; b++)
				{
					if (carte[a][b].getTerrain() != Terrain::aquatique && a < 32 && b < 32 && a >= 0 && b >= 0)
					{
						carte[a][b].setTerrain(Terrain::rocheux);
					}
				}
			}
		}
	}

	void Carte::genererObstacles()
	{

	}

	Case Carte::getCase(int x, int y)
	{
		return carte[x][y];
	}



}
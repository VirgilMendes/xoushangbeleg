#pragma once

#include "Grille.h";
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector> 

namespace Modele
{
	Grille::Grille()
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

		this->genererObstaclesRocheux();

		this->genererArbre( 20);

		this->genererAutreAsset(50);
	}

	void Grille::genererEau( int tailleMax) 
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

	void Grille::genererPlage( int circonferenceMax)
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

	void Grille::genererRocheux(int taille, int epaisseur)
	{
		int i ;
		int j ;
		int choixCote;
		
		choixCote = rand() % 4;
		switch (choixCote) // là on cherche le côté pour mettre la base collée au mur
		{
		case 0:
			i = 0;
			j = 0;
			while ( j < 32 )
			{
				if (carte[i][j].getTerrain() == Terrain::aquatique)
				{
					
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

					j = 0;
					i = 100;
				}
				i++;
			}
			i = rand() % 32;
			break;
		}

		carte[i][j].setTerrain(Terrain::rocheux);
		tabRocheux.push_back(Vecteur2<int>(i, j));
		int essais = 0;
		while (tabRocheux.size() < taille && essais < 5000)
		{
			choixCote = rand() % 4;
			switch (choixCote)
			{
			case 0:
				if (tabRocheux[tabRocheux.size() - 1].x - 2 >= 0 && tabRocheux[tabRocheux.size() - 1].x - 2 < 32 && tabRocheux[tabRocheux.size() - 1].y < 32 && tabRocheux[tabRocheux.size() - 1].y >= 0)
				{
					if (carte[tabRocheux[tabRocheux.size() - 1].x - 2][tabRocheux[tabRocheux.size() - 1].y].getTerrain() != Terrain::aquatique && carte[tabRocheux[tabRocheux.size() - 1].x - 2][tabRocheux[tabRocheux.size() - 1].y].getTerrain() != Terrain::rocheux)
					{
						carte[tabRocheux[tabRocheux.size() - 1].x - 1][tabRocheux[tabRocheux.size() - 1].y].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x - 1, tabRocheux[tabRocheux.size() - 1].y));
						carte[tabRocheux[tabRocheux.size() - 1].x - 1][tabRocheux[tabRocheux.size() - 1].y].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x - 1, tabRocheux[tabRocheux.size() - 1].y));
					}
				}
				break;
			case 1:
				if (tabRocheux[tabRocheux.size() - 1].x + 2 >= 0 && tabRocheux[tabRocheux.size() - 1].x + 2 < 32 && tabRocheux[tabRocheux.size() - 1].y < 32 && tabRocheux[tabRocheux.size() - 1].y >= 0)
				{
					if (carte[tabRocheux[tabRocheux.size() - 1].x + 2][tabRocheux[tabRocheux.size() - 1].y].getTerrain() != Terrain::aquatique && carte[tabRocheux[tabRocheux.size() - 1].x + 2][tabRocheux[tabRocheux.size() - 1].y].getTerrain() != Terrain::rocheux)
					{
						carte[tabRocheux[tabRocheux.size() - 1].x + 1][tabRocheux[tabRocheux.size() - 1].y].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x + 1, tabRocheux[tabRocheux.size() - 1].y));
						carte[tabRocheux[tabRocheux.size() - 1].x + 1][tabRocheux[tabRocheux.size() - 1].y].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x + 1, tabRocheux[tabRocheux.size() - 1].y));
					}
				}
				break;
			case 2:
				if (tabRocheux[tabRocheux.size() - 1].x >= 0 && tabRocheux[tabRocheux.size() - 1].x < 32 && tabRocheux[tabRocheux.size() - 1].y - 2 < 32 && tabRocheux[tabRocheux.size() - 1].y - 2 >= 0)
				{
					if (carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y - 1].getTerrain() != Terrain::aquatique && carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y - 1].getTerrain() != Terrain::rocheux)
					{
						carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y - 1].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x, tabRocheux[tabRocheux.size() - 1].y - 1));
						carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y - 1].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x, tabRocheux[tabRocheux.size() - 1].y - 1));
					}
				}
				break;
			case 3:
				if (tabRocheux[tabRocheux.size() - 1].x >= 0 && tabRocheux[tabRocheux.size() - 1].x < 32  && tabRocheux[tabRocheux.size() - 1].y + 2 < 32 && tabRocheux[tabRocheux.size() - 1].y + 2 >= 0)
				{
					if (carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y + 2].getTerrain() != Terrain::aquatique && carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y + 2].getTerrain() != Terrain::rocheux)
					{
						carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y + 1].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x, tabRocheux[tabRocheux.size() - 1].y + 1));
						carte[tabRocheux[tabRocheux.size() - 1].x][tabRocheux[tabRocheux.size() - 1].y + 1].setTerrain(Terrain::rocheux);
						tabRocheux.push_back(Vecteur2<int>(tabRocheux[tabRocheux.size() - 1].x, tabRocheux[tabRocheux.size() - 1].y + 1));
					}
				}
				break;
			}
			essais++;
		}

		
		for (int e = 0; e < tabRocheux.size(); e++) // on va effectuer un traitement sur tout le chemin de "rocheux" fait precedemment
		{
			for (int a = tabRocheux[e].x - epaisseur; a <= tabRocheux[e].x + epaisseur ; a++)
			{
				if (a != tabRocheux[e].x - epaisseur && a != tabRocheux[e].x + epaisseur)
				{
					for (int b = tabRocheux[e].y - epaisseur; b <= tabRocheux[e].y + epaisseur; b++)
					{
						if (carte[a][b].getTerrain() != Terrain::aquatique && a < 32 && b < 32 && a >= 0 && b >= 0)
						{
							carte[a][b].setTerrain(Terrain::rocheux);
						}
					}
				}
				else
				{
					for (int b = tabRocheux[e].y - epaisseur +1; b <= tabRocheux[e].y + epaisseur-1; b++)
					{
						if (carte[a][b].getTerrain() != Terrain::aquatique && a < 32 && b < 32 && a >= 0 && b >= 0)
						{
							carte[a][b].setTerrain(Terrain::rocheux);
						}
					}
				}
			}
		}
	}

	void Grille::genererObstaclesRocheux()
	{
		// generer murs terrains rocheux
		int randRocher;
		int rochersALaSuite = 0;
		int tailleSortie = 0;

		for (int i = 0; i < 32; i++) // parcours pour trouver les zones rocheuses
		{
			for (int j = 0; j < 32; j++)
			{
				if (carte[i][j].getTerrain() == Terrain::rocheux)
				{
					randRocher = rand() % 10;
					for (int a = i - 1; a <= i + 1; a++) // test des alentours de la case sur la quelle on est positionné
					{
						for (int b = j - 1; b <= j + 1; b++)
						{
							if (carte[a][b].getTerrain() != Terrain::rocheux && randRocher <= 7 && rochersALaSuite <= 10)
							{
								carte[i][j].setObstacle(Obstacle::rocher);
								rochersALaSuite = rochersALaSuite + 1;
							}
							else if (carte[a][b].getTerrain() != Terrain::rocheux && tailleSortie > 4)
							{
								rochersALaSuite = 0;
								tailleSortie = 0;
							}
							else if (carte[a][b].getTerrain() != Terrain::rocheux && rochersALaSuite > 10)
							{
								tailleSortie = tailleSortie + 1;
							}
							else if (i == 0 || i == 31 || j == 0 || j == 31 || carte[a][b].getTerrain() == Terrain::aquatique)
							{
								carte[i][j].setObstacle(Obstacle::rocher);
							}
						}
					}

				}
			}
		}
//apres avoir mis les frontières des zones rocheuses, on va y ajouter des murs... malheureusement, ça demande de retraverser les cases.
		int randMur;
		int randTailleMur;
		int randDirMur;
		int xMur;
		int yMur;
		int cheminSansMur;
		int limiteMur = 100;

		for (int i = 0; i < 32; i++) // parcours pour trouver les zones rocheuses
		{
			for (int j = 0; j < 32; j++)
			{
				if (carte[i][j].getTerrain() == Terrain::rocheux)
				{
					for (int a = i - 1; a <= i + 1; a++) // test des alentours de la case sur la quelle on est positionné
					{
						for (int b = j - 1; b <= j + 1; b++)
						{
							randMur = rand() % 100;
							if (carte[a][b].getObstacle() == Obstacle::rocher && randMur < 5 && limiteMur >= 0)
							{	
								limiteMur = limiteMur - 1;

							
								xMur = i;
								yMur = j;
								randTailleMur = rand() % 25;
								cheminSansMur = 0;
								while( cheminSansMur <= randTailleMur )
								{
									carte[xMur][yMur].setObstacle(Obstacle::rocher);
									randDirMur = rand() % 4;
									switch (randDirMur) // là on donne à chaque fois une nouvelle direction au mur
									{
									case 0:
										if (carte[xMur - 3][yMur].getObstacle() == Obstacle::rocher )
										{
											cheminSansMur = 100;
										}
										else if (carte[xMur - 1][yMur].getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = cheminSansMur - 1;
										}
										else if (xMur - 1 >= 0)
										{
											xMur = xMur - 1;
										}
										break;
									case 1:
										if (carte[xMur + 3][yMur].getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = 100;
										}
										else if (carte[xMur + 1][yMur].getObstacle() == Obstacle::rocher )
										{
											cheminSansMur = cheminSansMur - 1;
										}
										else if (xMur + 1 < 32)
										{
											xMur = xMur + 1;
										}
										break;
									case 2:
										if (carte[xMur][yMur - 3].getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = 100;
										}
										else if (carte[xMur][yMur - 1].getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = cheminSansMur - 1;
										}
										else if( yMur - 1 >= 0)
										{
											yMur = yMur - 1;
										}
										break;
									case 3:
										if (carte[xMur][yMur + 3].getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = 100;
										}
										else if (carte[xMur][yMur + 1].getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = cheminSansMur + 1;
										}
										else if (yMur + 1 < 32)
										{
											yMur = yMur + 1;
										}
										break;
									}
									cheminSansMur = cheminSansMur + 1;
								}
							}
						}
					}

				}
			}
		}
	}

	void Grille::genererArbre(int intensite)
	{
		int randNbArbre = 0;
		int randDirArbre = 1;
		int nbEssaisArbre;
		 

		int nouvelArbreX = 0;
		int nouvelArbreY;

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (carte[i][j].getObstacle() == Obstacle::rocher && carte[i][j].getTerrain() == Terrain::rocheux && rand() % 100 >= 90) //pour les arbres dans les grottes
				{
					carte[i][j].setObstacle(Obstacle::arbre); 
				}
				if (carte[i][j].getTerrain() == Terrain::sableux && rand() % 100 >= 98) //pour les arbres dans les plages
				{
					carte[i][j].setObstacle(Obstacle::arbre);
				}
				if (i == 31 || i == 0 || j == 31 || j == 0 )
				{
					if (carte[i][j].getTerrain() == Terrain::herbeux || carte[i][j].getTerrain() == Terrain::sableux) //pour les arbres sur les limites de terrain
					{
						carte[i][j].setObstacle(Obstacle::arbre);
					}
					if (rand() % 100 >= 70 && carte[i][j].getTerrain() == Terrain::herbeux )
					{
						if (i == 31 && j % 2 == 0 && j != 0)
						{
							carte[i-1][j].setObstacle(Obstacle::arbre);
							tabBaseArbreForet.push_back(Vecteur2<int>(i-1, j ));
	
						}
						else if (i == 0 && j % 2 == 0 && j != 0)
						{
							carte[i + 2][j ].setObstacle(Obstacle::arbre);
							tabBaseArbreForet.push_back(Vecteur2<int>(i + 2, j));
						
						}
						 else if ( i % 2 == 0 && i != 0 && j == 0 )
						{
							carte[i ][j + 2].setObstacle(Obstacle::arbre);
							tabBaseArbreForet.push_back(Vecteur2<int>(i , j+ 2 ));
						
						}
						 else if (i % 2 == 0 && i != 0 && j == 31 )
						{
							carte[i][j-1].setObstacle(Obstacle::arbre);
							tabBaseArbreForet.push_back(Vecteur2<int>(i, j-1));
					
						}
					}
				}
				else if (carte[i][j].getTerrain() == Terrain::rocheux && carte[i][j].getObstacle() == Obstacle::rocher)
				{
					for (int a = i - 1; a <= i + 1; a++)
					{
						for (int b = j - 1; b <= j + 1; b++)
						{
							if (carte[a][b].getTerrain() == Terrain::herbeux  && rand() % 100 >= 0 && a % 2 == 0 && b % 2 == 0)
							{
								nbEssaisArbre = 0;
						
								carte[a][b].setObstacle(Obstacle::arbre);
								tabBaseArbreForet.push_back(Vecteur2<int>(a, b));

							}
						}
					}
				}
			}
		}
		int randTailleForet = 0;
		bool tour = true;
	
		for (int i = 0; i < tabBaseArbreForet.size(); i++)
		{
			randTailleForet = rand() % intensite;		
			if (tabBaseArbreForet[i].x < 15 && tabBaseArbreForet[i].y < 15)
			{
			
				for (int t = 0; t < randTailleForet; t++)
				{
					if (t % 2 == 0)
					{
						if (tour && carte[tabBaseArbreForet[i].x + 2][tabBaseArbreForet[i].y].getTerrain() == Terrain::herbeux)
						{
							carte[tabBaseArbreForet[i].x + 2][tabBaseArbreForet[i].y].setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].x = tabBaseArbreForet[i].x + 2;
							tour = false;
						}
						else if (carte[tabBaseArbreForet[i].x ][tabBaseArbreForet[i].y+2].getTerrain() == Terrain::herbeux)
						{
							carte[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y +2].setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].y = tabBaseArbreForet[i].y + 2;
							tour = true;
						}
					}
				}
			}
			if (tabBaseArbreForet[i].x >= 15 && tabBaseArbreForet[i].y < 15)
			{
				for (int t = 0; t < randTailleForet; t++)
				{
					if (t % 2 == 0)
					{
						if (tour && carte[tabBaseArbreForet[i].x - 2][tabBaseArbreForet[i].y].getTerrain() == Terrain::herbeux)
						{
							carte[tabBaseArbreForet[i].x - 2][tabBaseArbreForet[i].y].setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].x = tabBaseArbreForet[i].x - 2;
							tour = false;
						}
						else if (carte[tabBaseArbreForet[i].x ][tabBaseArbreForet[i].y+2].getTerrain() == Terrain::herbeux)
						{
							carte[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y + 2].setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].y = tabBaseArbreForet[i].y +2;
							tour = true;
						}
					}
				}
			}
			if (tabBaseArbreForet[i].x < 15 && tabBaseArbreForet[i].y >= 15)
			{
				for (int t = 0; t < randTailleForet; t++)
				{
					if (t % 2 == 0)
					{
						if (tour && carte[tabBaseArbreForet[i].x + 2][tabBaseArbreForet[i].y].getTerrain() == Terrain::herbeux)
						{
							carte[tabBaseArbreForet[i].x + 2][tabBaseArbreForet[i].y].setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].x = tabBaseArbreForet[i].x + 2;
							tour = false;
						}
						else  if (carte[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y-2].getTerrain() == Terrain::herbeux)
						{
							carte[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y -2].setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].y = tabBaseArbreForet[i].y - 2;
							tour = true;
						}
					}
				}
			}
			if (tabBaseArbreForet[i].x >= 15 && tabBaseArbreForet[i].y >= 15)
			{
				for (int t = 0; t < randTailleForet; t++)
				{
					if (t % 2 == 0)
					{
						if (tour && carte[tabBaseArbreForet[i].x - 2][tabBaseArbreForet[i].y].getTerrain() == Terrain::herbeux)
						{
							carte[tabBaseArbreForet[i].x - 2 ][tabBaseArbreForet[i].y].setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].x = tabBaseArbreForet[i].x - 2;
							tour = false;
						}
						else  if (carte[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y-2].getTerrain() == Terrain::herbeux)
						{
							carte[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y - 2].setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].y = tabBaseArbreForet[i].y - 2;
							tour = true;
						}
					}
				}
			}
			
		}
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (carte[i][j].getTerrain() == Terrain::rocheux && carte[i][j].getObstacle() == Obstacle::aucun)
				{
					for (int a = i - 1; a <= i + 1; a++)
					{
						for (int b = j - 1; b <= j + 1; b++)
						{
							if (carte[a][b].getTerrain() == Terrain::herbeux)
							{
								carte[a][b].setObstacle(Obstacle::aucun);
							}
						}
					}
				}
			}
		}
	}

	void Grille::genererAutreAsset( int nbTotal)
	{
		int randI;
		int randJ;
		int randTypeObstacle;
		for (int t = 0; t < nbTotal; t++)
		{
			randI = rand() % 32;
			randJ = rand() % 32;
			switch (rand() % 2)
			{
			case 0:
				carte[randI][randJ].setObstacle(Obstacle::buisson);
				break;
			case 1:
				if (carte[randI][randJ].getTerrain() != Terrain::rocheux)
				{
					carte[randI][randJ].setObstacle(Obstacle::rocher);
				}
				break;
			}
			
		}
	}

	Case Grille::getCase(int x, int y)
	{
		return carte[x][y];
	}


}
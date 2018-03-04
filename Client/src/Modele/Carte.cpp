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

		this->genererObstaclesRocheux();

		this->genererArbre();
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

	void Carte::genererObstaclesRocheux()
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

	void Carte::genererArbre()
	{
		/*int randNbArbre = 0;
		int randDirArbre = 1;
		int nbEssaisArbre;
		 

		int nouvelArbreX = 0;
		int nouvelArbreY;

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (carte_[i][j].getObstacle() == Obstacle::rocher && carte_[i][j].getTerrain() == Terrain::rocheux && rand() % 100 >= 90) //pour les arbres dans les grottes
				{
					carte_[i][j].setObstacle(Obstacle::arbre); 
				}
				/*if (carte_[i][j].getTerrain() == Terrain::sableux && rand() % 100 >= 95) //pour les arbres dans les plages
				{
					carte_[i][j].setObstacle(Obstacle::arbre);
				}
				if (i == 31 || i == 0 || j == 31 || j == 0 )
				{
					if (carte_[i][j].getTerrain() == Terrain::herbeux || carte_[i][j].getTerrain() == Terrain::sableux) //pour les arbres sur les limites de terrain
					{
						carte_[i][j].setObstacle(Obstacle::arbre);
					}
				}
				else if (carte_[i][j].getTerrain() == Terrain::herbeux && i%2 == 0 && j%2 == 0)
				{
					for (int a = i - 1; a <= i + 1; a++)
					{
						for (int b = j - 1; b <= j + 1; b++)
						{
							std::cout << "   i  =  " << i << "   j  =  " << j ;
							std::cout << "  /   a  =  " << a << "   b  =  " << b << std::endl;
							/*if (( carte_[a][b].getObstacle() == Obstacle::rocher)  && rand() % 100 >= 85)
							{
								nbEssaisArbre = 0;
								std::cout << "		 base démarrée aux coord : i = " << i << "  /  j = " << j << std::endl;
								carte_[i][j].setObstacle(Obstacle::arbre);
								tabBaseArbreForet.push_back(Vecteur2<int>(i, j));

								/*randNbArbre = rand() % 20;
								while (randDirArbre % 2 != 0)
								{
									randDirArbre = rand() % 7;

								}
								while (randNbArbre != 0 && nbEssaisArbre < 100)
								{
									std::cout << "  /  randNbArbre au debut  =  " << randNbArbre<< std::endl;
									switch (rand() % 8)
									{
									case (0) :
										if (carte_[i + randDirArbre][j].getTerrain() == Terrain::herbeux && i + randDirArbre < 32)
										{
											std::cout << "  / arbre placé aux coord : i + = " << i + randDirArbre << "  /  j = " << j << std::endl;
											carte_[i + randDirArbre][j].setObstacle(Obstacle::arbre);
											randNbArbre = randNbArbre - 1;
										}
										else
										std::cout <<"  / case 0 refuse : "<< carte_[i + randDirArbre][j].getObstacle()<<  std::endl;
										nbEssaisArbre = nbEssaisArbre + 1;
										break;
									case (1) :
										if (carte_[i ][j + randDirArbre].getTerrain() == Terrain::herbeux  && j + randDirArbre < 32)
										{
											std::cout << "  / arbre placé aux coord : i  = " << i << "  /  j + = " << j + randDirArbre << std::endl;
											carte_[i ][j + randDirArbre].setObstacle(Obstacle::arbre);
											randNbArbre = randNbArbre - 1;
										}
										else
										std::cout << " case 1 refuse :" << carte_[i][j + randDirArbre].getObstacle()<< std::endl;
										nbEssaisArbre = nbEssaisArbre + 1;
										break;
									case (2) :
										if (carte_[i + randDirArbre][j + randDirArbre].getTerrain() == Terrain::herbeux  && i + randDirArbre < 32 && j + randDirArbre < 32)
										{
											std::cout << "  / arbre placé aux coord : i + = " << i + randDirArbre << "  /  j + = " << j + randDirArbre << std::endl;
											carte_[i + randDirArbre][j + randDirArbre].setObstacle(Obstacle::arbre);
											randNbArbre = randNbArbre - 1;
										}
										else
										std::cout << " case 2 refuse : " << carte_[i + randDirArbre][j + randDirArbre].getObstacle()<< std::endl;
										nbEssaisArbre = nbEssaisArbre + 1;
										break;
									case (3) :
										if (carte_[i - randDirArbre][j].getTerrain() == Terrain::herbeux  && i - randDirArbre >= 0)
										{
											std::cout << "  / arbre placé aux coord : i - = " << i - randDirArbre << "  /  j = " << j << std::endl;
											carte_[i - randDirArbre][j].setObstacle(Obstacle::arbre);
											randNbArbre = randNbArbre - 1;
										}
										else
										std::cout << " case 3 refuse :  coord : "<< carte_[i - randDirArbre][j].getObstacle()<< std::endl;
										nbEssaisArbre = nbEssaisArbre + 1;
										break;
									case (4):
										if (carte_[i ][j - randDirArbre].getTerrain() == Terrain::herbeux  && j - randDirArbre >= 0)
										{
											std::cout << "  / arbre placé aux coord : " << std::endl;
											carte_[i ][j - randDirArbre].setObstacle(Obstacle::arbre);
											randNbArbre = randNbArbre - 1;
										}
										else
										std::cout << " case 4 refuse :"<< carte_[i][j - randDirArbre].getObstacle()<< std::endl;
										nbEssaisArbre = nbEssaisArbre + 1;
										break;
									case (5):
										if (carte_[i - randDirArbre][j - randDirArbre].getTerrain() == Terrain::herbeux && i - randDirArbre >=0 && j - randDirArbre >=0)
										{
											std::cout << "  / arbre placé aux coord : i - = " << i - randDirArbre << "  /  j - = " << j - randDirArbre << std::endl;
											carte_[i - randDirArbre][j - randDirArbre].setObstacle(Obstacle::arbre);
											randNbArbre = randNbArbre - 1;
										}
										else
										std::cout << " case 5 refuse : " << carte_[i - randDirArbre][j - randDirArbre].getObstacle()<< std::endl;
										nbEssaisArbre = nbEssaisArbre + 1;
										break;
									case (6):
										if (carte_[i + randDirArbre][j - randDirArbre].getTerrain() == Terrain::herbeux && i + randDirArbre < 32 && j - randDirArbre >= 0)
										{
											std::cout << "  / arbre placé aux coord : i + = " << i + randDirArbre << "  /  j - = " << j - randDirArbre << std::endl;
											carte_[i + randDirArbre][j - randDirArbre].setObstacle(Obstacle::arbre);
											randNbArbre = randNbArbre - 1;
										}
										else
										std::cout << " case 6 refuse : " << carte_[i + randDirArbre][j - randDirArbre].getObstacle()<<std::endl;
										nbEssaisArbre = nbEssaisArbre + 1;
										break;
									case (7):
										if (carte_[i - randDirArbre][j + randDirArbre].getTerrain() == Terrain::herbeux  && i - randDirArbre >= 0 && j + randDirArbre < 32)
										{
											std::cout << "  / arbre placé aux coord : i - = " << i - randDirArbre << "  /  j + = " << j + randDirArbre << std::endl;
											carte_[i - randDirArbre][j + randDirArbre].setObstacle(Obstacle::arbre);
											randNbArbre = randNbArbre - 1;
										}

										std::cout << " case 7 refuse : "<< carte_[i - randDirArbre][j + randDirArbre].getObstacle()<< std::endl;
										nbEssaisArbre = nbEssaisArbre + 1;
										break;
									default:
										std::cout << " dir trouvee : " << std::endl;
										break;
									}
									
									randDirArbre = 1;
									
								}
								std::cout << "  /  randNbArbre  =  " << randNbArbre;
								std::cout << "    /  nbEssaisArbre  =  " << nbEssaisArbre << std::endl;
								std::cout  << std::endl;
								
							}
						}
					}
				}
			}
		}*/
	}

	Case Carte::getCase(int x, int y)
	{
		return carte[x][y];
	}


}
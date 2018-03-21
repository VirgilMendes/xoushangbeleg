#pragma once

#include "Grille.h";
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <pugixml.hpp>
#include <sstream>
#include "../Controleur/DonneeServeur.h"


namespace Modele
{
	Grille::Grille(const Vecteur2<int>& dimension) : dimension_(dimension), proprietaireDerniereRechercheDeplacement_(nullptr)
	{
		srand((unsigned)time(NULL));

		for (int i = 0; i < dimension_.y; i++)
		{
			cases_.push_back(std::vector<Case*>());
			for (int j = 0; j < dimension_.x; j++)
			{
				cases_[i].push_back(new Case(Vecteur2<int>(j, i)));
			}
		}

		//Generation procedurale
		genererEau(100);
		genererPlage(5);
		genererRocheux(50, 5);
		genererObstaclesRocheux();
		genererArbre(20);
		genererAutreAsset(50);
	}

	Grille::Grille(std::vector<std::vector<Case*>> cases, std::set<Unite*, ComparateurPointeurUniteNom> unites) : dimension_(Vecteur2<int>(cases[0].size(), cases.size())),
		cases_(cases), unites_(unites), proprietaireDerniereRechercheDeplacement_(nullptr), proprietaireDerniereRechercheAttaque_(nullptr)
	{
		for(Unite *unite : unites)
		{
			getCase(unite->getPosition())->setUnite(unite);
		}
	}

	Grille::~Grille()
	{
		for (auto ligne : cases_)
			for (Case* caseGrille : ligne)
				delete caseGrille;
		for (auto iterateur(unites_.begin()); iterateur != unites_.end(); ++iterateur)
			delete *iterateur;
	}

	Case* Grille::getCase(const Vecteur2<int>& coordonees)
	{
		return cases_.at(coordonees.y).at(coordonees.x);
	}

	Case* Grille::getCase(const int x, const int y)
	{
		return cases_.at(y).at(x);
	}

	Unite* Grille::getUnite(const std::string& nom)
	{
		for (auto iterateur(unites_.begin()); iterateur != unites_.end(); ++iterateur)
		{
			if ((*iterateur)->getNom() == nom)
				return *iterateur;
		}
		return nullptr;
	}

	void Grille::ajouterUnite(Unite* unite)
	{
		unites_.insert(unite);
		getCase(unite->getPosition())->setUnite(unite);
	}

	void Grille::supprimerUnite(Unite* unite)
	{
		for (auto iterateur(unites_.begin()); iterateur != unites_.end(); ++iterateur)
		{
			if ((*iterateur) == unite)
			{
				getCase(unite->getPosition())->setUnite(nullptr);
				unites_.erase(iterateur);
				ordreDeJeu_.erase(unite);
				delete unite;
				return;
			}
		}
	}

	Unite* Grille::getUniteActuel()
	{
		if (ordreDeJeu_.empty()) return nullptr;
		return *ordreDeJeu_.rbegin();
	}

	void Grille::finDeTour()
	{
		if (!ordreDeJeu_.empty())
		{
			ordreDeJeu_.erase((++ordreDeJeu_.rbegin()).base());
		}
	}

	void Grille::relancerOrdreDeJeu()
	{
		for (Unite* unite : unites_)
			ordreDeJeu_.insert(unite);
	}

	std::stack<Vecteur2<int>> Grille::chercherChemin(const Vecteur2<int>& cible)
	{
		Case* caseCourante = getCase(cible);
		std::stack<Vecteur2<int>> chemin;
		while(caseCourante->getCaseParent() != nullptr)
		{
			chemin.push(caseCourante->getPosition());
			caseCourante = caseCourante->getCaseParent();
		}
		return chemin;
	}

	void Grille::nettoyerDerniereRechercheDeplacement()
	{
		for (auto iterateur(derniereRechercheDeplacement_.begin()); iterateur != derniereRechercheDeplacement_.end(); ++iterateur)
		{
			Case* caseRecherche = getCase(*iterateur);
			caseRecherche->setCout(INT32_MAX);
			caseRecherche->setCaseParent(nullptr);
		}
		derniereRechercheDeplacement_.clear();
	}

	void Grille::nettoyerDerniereRechercheAttaque()
	{
		for (auto iterateur(derniereRechercheAttaque_.begin()); iterateur != derniereRechercheAttaque_.end(); ++iterateur)
			getCase(*iterateur)->setCout(INT32_MAX);
		derniereRechercheAttaque_.clear();
	}

	std::forward_list<Vecteur2<int>> Grille::getCoordonneesCasesAdjacentes(const Vecteur2<int>& coordonnees)
	{
		getCase(coordonnees);
		std::forward_list<Vecteur2<int>> coordonneeCasesAdjacentes;
		if (coordonnees.y + 1 < dimension_.y)
			coordonneeCasesAdjacentes.push_front(coordonnees + Vecteur2<int>::NORD);
		if (coordonnees.x + 1 < dimension_.x)
			coordonneeCasesAdjacentes.push_front(coordonnees + Vecteur2<int>::EST);
		if (coordonnees.y > 0)
			coordonneeCasesAdjacentes.push_front(coordonnees + Vecteur2<int>::SUD);
		if (coordonnees.x > 0)
			coordonneeCasesAdjacentes.push_front(coordonnees + Vecteur2<int>::OUEST);

		return coordonneeCasesAdjacentes;
	}	

	std::list<Vecteur2<int>> Grille::chercherCasesAccessiblesDeplacement(const Vecteur2<int>& depart, const int rayon)
	{
		nettoyerDerniereRechercheDeplacement();

		auto comparateurCaseCout = [](Case* a, Case* b) {return (a->getCout() > b->getCout()); };
		std::priority_queue < Case*, std::vector<Case*>, decltype(comparateurCaseCout)> analyser(comparateurCaseCout);

		Case* caseDepart = getCase(depart);

		proprietaireDerniereRechercheDeplacement_ = caseDepart->getUnite();

		caseDepart->setCout(0);

		analyser.push(caseDepart);

		while (!analyser.empty())
		{
			Case* caseCourante = analyser.top();
			analyser.pop();
			const int coutCaseCourante = caseCourante->getCout();
			derniereRechercheDeplacement_.push_back(caseCourante->getPosition());

			for (const Vecteur2<int> coordonneesCasesAdjacente : getCoordonneesCasesAdjacentes(caseCourante->getPosition()))
			{
				Case* caseAdjacente = getCase(coordonneesCasesAdjacente);
				if(coutCaseCourante + 1 <= rayon && coutCaseCourante + 1 < caseAdjacente->getCout())
				{
					if (caseAdjacente->getObstacle()._to_integral() == 0 && caseAdjacente->getTerrain()._to_integral()!=2 && caseAdjacente->getUnite() == nullptr)
					{
						caseAdjacente->setCout(caseCourante->getCout() + 1);
						caseAdjacente->setCaseParent(caseCourante);
						analyser.push(caseAdjacente);
					}
				}
			}
		}
		return derniereRechercheDeplacement_;
	}

	std::list<Vecteur2<int>> Grille::chercherCasesAccessiblesAttaque(const Vecteur2<int>& depart, const int rayon)
	{
		nettoyerDerniereRechercheAttaque();

		auto comparateurCaseCout = [](Case* a, Case* b) {return (a->getCout() > b->getCout()); };
		std::priority_queue < Case*, std::vector<Case*>, decltype(comparateurCaseCout)> analyser(comparateurCaseCout);

		Case* caseDepart = getCase(depart);

		proprietaireDerniereRechercheAttaque_ = caseDepart->getUnite();

		caseDepart->setCout(0);

		analyser.push(caseDepart);

		while (!analyser.empty())
		{
			Case* caseCourante = analyser.top();
			analyser.pop();
			const int coutCaseCourante = caseCourante->getCout();
			derniereRechercheAttaque_.push_back(caseCourante->getPosition());

			for (const Vecteur2<int> coordonneesCasesAdjacente : getCoordonneesCasesAdjacentes(caseCourante->getPosition()))
			{
				Case* caseAdjacente = getCase(coordonneesCasesAdjacente);
				if (coutCaseCourante + 1 <= rayon && coutCaseCourante + 1 < caseAdjacente->getCout())
				{
					caseAdjacente->setCout(caseCourante->getCout() + 1);
					analyser.push(caseAdjacente);
				}
			}
		}
		return derniereRechercheAttaque_;
	}

	void Grille::deplacerUnite(const std::string& nom, const Vecteur2<int>& destination)
	{
		Unite* unite = getUnite(nom);
		if (unite != nullptr)
		{
			getCase(unite->getPosition())->setUnite(nullptr);
			unite->deplacer(destination);
			getCase(destination)->setUnite(unite);
		}
	}

	void Grille::deplacerUnite(Unite* unite, const Vecteur2<int>& deplacement)
	{
		if (std::find(unites_.begin(), unites_.end(), unite) != unites_.end())
		{
			getCase(unite->getPosition())->setUnite(nullptr);
			unite->deplacer(deplacement);
			getCase(unite->getPosition())->setUnite(unite);
		}
	}

	void Grille::genererEau(const int tailleMax)
	{
		const Vecteur2<int> start(rand() % 32, rand() % 32);
		getCase(start)->setTerrain(Terrain::aquatique);
		casesAquatiques_.push_back(start);

		int nombreEssais(0);

		while (casesAquatiques_.size() < tailleMax && nombreEssais < 1000)
		{

			//on prend une case d'eau aleatoire afin de l'entourer de case d'eau
			const Vecteur2<int> randomCaseAquatique = casesAquatiques_[rand() % casesAquatiques_.size()];

			for (int i = randomCaseAquatique.x - 1; i <= randomCaseAquatique.x + 1; i++)
			{
				for (int j = randomCaseAquatique.y - 1; j <= randomCaseAquatique.y + 1; j++)
				{
					if (i < 32 && j < 32 && i >= 0 && j >= 0)
					{
						if (getCase(i, j)->getTerrain() == Terrain::herbeux)
						{
							getCase(i, j)->setTerrain(Terrain::aquatique);
							casesAquatiques_.push_back(Vecteur2<int>(i, j));
						}
					}
					nombreEssais = ++nombreEssais;
				}
			}
		}
	}

	void Grille::genererPlage(const int circonferenceMax)
	{
		for (const Vecteur2<int> caseAquatique : casesAquatiques_)
		{
			const int tailleVoisinageEau = rand() % circonferenceMax + 1;

			//on genere une ligne de sable avec pour centre le point d'eau
			for (int i = caseAquatique.x - tailleVoisinageEau; i <= caseAquatique.x + tailleVoisinageEau; i++)
			{
				if (i < 32 && i >= 0)
				{
					Case* casePotentiel = getCase(i, caseAquatique.y);

					if (casePotentiel->getTerrain() == Terrain::herbeux)
					{
						casePotentiel->setTerrain(Terrain::sableux);
					}
				}
			}

			//on genere une colonne de sable avec pour centre le point d'eau
			for (int j = caseAquatique.y - tailleVoisinageEau; j <= caseAquatique.y + tailleVoisinageEau; j++)
			{
				if (j < 32 && j >= 0)
				{
					Case* casePotentiel = getCase(caseAquatique.x, j);
					if (casePotentiel->getTerrain() == Terrain::herbeux)
					{
						casePotentiel->setTerrain(Terrain::sableux);
					}
				}
			}

			int i = 0 + tailleVoisinageEau;
			int j = 0 - tailleVoisinageEau;

			while (j <= tailleVoisinageEau && i >= -tailleVoisinageEau)
			{
				if (caseAquatique.x + i < 32 && caseAquatique.x + i >= 0 && caseAquatique.y + j < 32 && caseAquatique.y + j >= 0)
				{
					Case* casePotentiel = getCase(caseAquatique.x + i, caseAquatique.y + j);

					if (casePotentiel->getTerrain() == Terrain::herbeux)
					{
						casePotentiel->setTerrain(Terrain::sableux);
					}
				}
				i -= 1;
				j += 1;
			}

			i = 0 - tailleVoisinageEau;
			while (i <= tailleVoisinageEau)
			{
				if (caseAquatique.x + i < 32 && caseAquatique.x + i >= 0 && caseAquatique.y + i < 32 && caseAquatique.y + i >= 0)
				{
					Case* casePotentiel = getCase(caseAquatique.x + i, caseAquatique.y + i);

					if (casePotentiel->getTerrain() == Terrain::herbeux)
					{
						casePotentiel->setTerrain(Terrain::sableux);
					}
				}
				i += 1;
			}
		}
	}

	void Grille::genererRocheux(int taille, int epaisseur)
	{
		int i;
		int j;
		int choixCote;

		choixCote = rand() % 4;
		switch (choixCote) // la on cherche le cote pour mettre la base collee au mur
		{
		case 0:
			i = 0;
			j = 0;
			while (j < 32)
			{
				if (cases_[i][j]->getTerrain() == Terrain::aquatique)
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
				if (cases_[i][j]->getTerrain() == Terrain::aquatique)
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
				if (cases_[i][j]->getTerrain() == Terrain::aquatique)
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
				if (cases_[i][j]->getTerrain() == Terrain::aquatique)
				{
					j = 0;
					i = 100;
				}
				i++;
			}
			i = rand() % 32;
			break;
		}

		cases_[i][j]->setTerrain(Terrain::rocheux);
		casesRocheuses_.push_back(Vecteur2<int>(i, j));
		int essais = 0;
		while (casesRocheuses_.size() < taille && essais < 5000)
		{
			choixCote = rand() % 4;
			const Vecteur2<int> caseRocheuse = casesRocheuses_[casesRocheuses_.size() - 1];
			switch (choixCote)
			{
			case 0:
				 
				if (caseRocheuse.x - 2 >= 0 && caseRocheuse.x - 2 < 32
					&& caseRocheuse.y < 32 && caseRocheuse.y >= 0)
				{
					if (cases_[caseRocheuse.x - 2][caseRocheuse.y]->getTerrain() != Terrain::aquatique 
						&& cases_[caseRocheuse.x - 2][caseRocheuse.y]->getTerrain() != Terrain::rocheux)
					{
						cases_[caseRocheuse.x - 1][caseRocheuse.y]->setTerrain(Terrain::rocheux);
						casesRocheuses_.push_back(Vecteur2<int>(caseRocheuse.x - 1, caseRocheuse.y));
						cases_[caseRocheuse.x - 1][caseRocheuse.y]->setTerrain(Terrain::rocheux);
						casesRocheuses_.push_back(Vecteur2<int>(caseRocheuse.x - 1, caseRocheuse.y));
					}
				}
				break;
			case 1:
				if (caseRocheuse.x + 2 >= 0 && caseRocheuse.x + 2 < 32
					&& caseRocheuse.y < 32 && caseRocheuse.y >= 0)
				{
					if (cases_[caseRocheuse.x + 2][caseRocheuse.y]->getTerrain() != Terrain::aquatique 
						&& cases_[caseRocheuse.x + 2][caseRocheuse.y]->getTerrain() != Terrain::rocheux)
					{
						cases_[caseRocheuse.x + 1][caseRocheuse.y]->setTerrain(Terrain::rocheux);
						casesRocheuses_.push_back(Vecteur2<int>(caseRocheuse.x + 1, caseRocheuse.y));
						cases_[caseRocheuse.x + 1][caseRocheuse.y]->setTerrain(Terrain::rocheux);
						casesRocheuses_.push_back(Vecteur2<int>(caseRocheuse.x + 1, caseRocheuse.y));
					}
				}
				break;
			case 2:
				if (caseRocheuse.x >= 0 && caseRocheuse.x < 32 &&
					caseRocheuse.y - 2 < 32 && caseRocheuse.y - 2 >= 0)
				{
					if (cases_[caseRocheuse.x][caseRocheuse.y - 1]->getTerrain() != Terrain::aquatique 
						&& cases_[caseRocheuse.x][caseRocheuse.y - 1]->getTerrain() != Terrain::rocheux)
					{
						cases_[caseRocheuse.x][caseRocheuse.y - 1]->setTerrain(Terrain::rocheux);
						casesRocheuses_.push_back(Vecteur2<int>(caseRocheuse.x, caseRocheuse.y - 1));
						cases_[caseRocheuse.x][caseRocheuse.y - 1]->setTerrain(Terrain::rocheux);
						casesRocheuses_.push_back(Vecteur2<int>(caseRocheuse.x, caseRocheuse.y - 1));
					}
				}
				break;
			case 3:
				if (caseRocheuse.x >= 0 && caseRocheuse.x < 32 &&
					caseRocheuse.y + 2 < 32 && caseRocheuse.y + 2 >= 0)
				{
					if (cases_[caseRocheuse.x][caseRocheuse.y + 2]->getTerrain() != Terrain::aquatique
						&& cases_[caseRocheuse.x][caseRocheuse.y + 2]->getTerrain() != Terrain::rocheux)
					{
						cases_[caseRocheuse.x][caseRocheuse.y + 1]->setTerrain(Terrain::rocheux);
						casesRocheuses_.push_back(Vecteur2<int>(caseRocheuse.x, caseRocheuse.y + 1));
						cases_[caseRocheuse.x][caseRocheuse.y + 1]->setTerrain(Terrain::rocheux);
						casesRocheuses_.push_back(Vecteur2<int>(caseRocheuse.x, caseRocheuse.y + 1));
					}
				}
				break;
			}
			essais++;
		}

		
		for (int e = 0; e < casesRocheuses_.size(); e++)	
		{
			// on va effectuer un traitement sur tout le chemin de "rocheux" fait precedemment

			const Vecteur2<int> caseRocheuse = casesRocheuses_[e];
			for (int a = caseRocheuse.x - epaisseur; a <= caseRocheuse.x + epaisseur; a++)
			{
				if (a != caseRocheuse.x - epaisseur && a != caseRocheuse.x + epaisseur)
				{
					for (int b = caseRocheuse.y - epaisseur; b <= caseRocheuse.y + epaisseur; b++)
					{
						if ( a < 32 && b < 32 && a >= 0 && b >= 0 &&cases_[a][b]->getTerrain() != Terrain::aquatique )
						{
							cases_[a][b]->setTerrain(Terrain::rocheux);
						}
					}
				}
				else
				{
					for (int b = caseRocheuse.y - epaisseur + 1; b <= caseRocheuse.y + epaisseur - 1; b++)
					{
						if (a < 32 && b < 32 && a >= 0 && b >= 0 && cases_[a][b]->getTerrain() != Terrain::aquatique)
						{
							cases_[a][b]->setTerrain(Terrain::rocheux);
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
				if (cases_[i][j]->getTerrain() == Terrain::rocheux)
				{
					randRocher = rand() % 10;
					for (int a = i - 1; a <= i + 1; a++) // test des alentours de la case sur la quelle on est positionn�
					{
						if (!(a < 32 && a >= 0))
							continue;
						for (int b = j - 1; b <= j + 1; b++)
						{
							if (!(b < 32 && b >= 0))
								continue;
							if (cases_[a][b]->getTerrain() != Terrain::rocheux && randRocher <= 7 && rochersALaSuite <= 10)
							{
								cases_[i][j]->setObstacle(Obstacle::rocher);
								rochersALaSuite = rochersALaSuite + 1;
							}
							else if (cases_[a][b]->getTerrain() != Terrain::rocheux && tailleSortie > 4)
							{
								rochersALaSuite = 0;
								tailleSortie = 0;
							}
							else if (cases_[a][b]->getTerrain() != Terrain::rocheux && rochersALaSuite > 10)
							{
								tailleSortie = tailleSortie + 1;
							}
							else if (i == 0 || i == 31 || j == 0 || j == 31 || cases_[a][b]->getTerrain() == Terrain::aquatique)
							{
								cases_[i][j]->setObstacle(Obstacle::rocher);
							}
						}
					}
				}
			}
		}
		//apres avoir mis les frontieres des zones rocheuses, on va y ajouter des murs... malheureusement, �a demande de retraverser les cases.
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
				if (cases_[i][j]->getTerrain() == Terrain::rocheux)
				{
					for (int a = i - 1; a <= i + 1; a++) // test des alentours de la case sur la quelle on est positionne
					{
						if(!(a < 32 && a >= 0))
							continue;
						for (int b = j - 1; b <= j + 1; b++)
						{
							if(!(b < 32 && b >=0))
								continue;
							randMur = rand() % 100;
							if (cases_[a][b]->getObstacle() == Obstacle::rocher && randMur < 5 && limiteMur >= 0)
							{
								limiteMur = limiteMur - 1;


								xMur = i;
								yMur = j;
								randTailleMur = rand() % 25;
								cheminSansMur = 0;
								while (cheminSansMur <= randTailleMur)
								{
									cases_[xMur][yMur]->setObstacle(Obstacle::rocher);
									randDirMur = rand() % 4;
									switch (randDirMur) // la on donne a chaque fois une nouvelle direction au mur
									{
									case 0:
										if ((xMur - 3) >= 0 && cases_[xMur - 3][yMur]->getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = 100;
										}
										else if ((xMur - 1) >=0 &&  cases_[xMur - 1][yMur]->getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = cheminSansMur - 1;
										}
										else if (xMur - 1 >= 0)
										{
											xMur = xMur - 1;
										}
										break;
									case 1:
										if ((xMur + 3) < 32 && cases_[xMur + 3][yMur]->getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = 100;
										}
										else if ((xMur + 1) < 32 &&  cases_[xMur + 1][yMur]->getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = cheminSansMur - 1;
										}
										else if (xMur + 1 < 32)
										{
											xMur = xMur + 1;
										}
										break;
									case 2:
										if ((yMur - 3) >=0 &&  cases_[xMur][yMur - 3]->getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = 100;
										}
										else if ((yMur - 1) >= 0 &&  cases_[xMur][yMur - 1]->getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = cheminSansMur - 1;
										}
										else if (yMur - 1 >= 0)
										{
											yMur = yMur - 1;
										}
										break;
									case 3:
										if ((yMur + 3) < 32 &&  cases_[xMur][yMur + 3]->getObstacle() == Obstacle::rocher)
										{
											cheminSansMur = 100;
										}
										else if ((yMur + 1) < 32 && cases_[xMur][yMur + 1]->getObstacle() == Obstacle::rocher)
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
				if (cases_[i][j]->getObstacle() == Obstacle::rocher && cases_[i][j]->getTerrain() == Terrain::rocheux && rand() % 100 >= 90) //pour les arbres dans les grottes
				{
					cases_[i][j]->setObstacle(Obstacle::arbre);
				}
				if (cases_[i][j]->getTerrain() == Terrain::sableux && rand() % 100 >= 98) //pour les arbres dans les plages
				{
					cases_[i][j]->setObstacle(Obstacle::arbre);
				}
				if (i == 31 || i == 0 || j == 31 || j == 0)
				{
					if (cases_[i][j]->getTerrain() == Terrain::herbeux || cases_[i][j]->getTerrain() == Terrain::sableux) //pour les arbres sur les limites de terrain
					{
						cases_[i][j]->setObstacle(Obstacle::arbre);
					}
					if (rand() % 100 >= 70 && cases_[i][j]->getTerrain() == Terrain::herbeux)
					{
						if (i == 31 && j % 2 == 0 && j != 0)
						{
							cases_[i - 1][j]->setObstacle(Obstacle::arbre);
							tabBaseArbreForet.push_back(Vecteur2<int>(i - 1, j));

						}
						else if (i == 0 && j % 2 == 0 && j != 0)
						{
							cases_[i + 2][j]->setObstacle(Obstacle::arbre);
							tabBaseArbreForet.push_back(Vecteur2<int>(i + 2, j));

						}
						else if (i % 2 == 0 && i != 0 && j == 0)
						{
							cases_[i][j + 2]->setObstacle(Obstacle::arbre);
							tabBaseArbreForet.push_back(Vecteur2<int>(i, j + 2));

						}
						else if (i % 2 == 0 && i != 0 && j == 31)
						{
							cases_[i][j - 1]->setObstacle(Obstacle::arbre);
							tabBaseArbreForet.push_back(Vecteur2<int>(i, j - 1));

						}
					}
				}
				else if (cases_[i][j]->getTerrain() == Terrain::rocheux && cases_[i][j]->getObstacle() == Obstacle::rocher)
				{
					for (int a = i - 1; a <= i + 1; a++)
					{
						for (int b = j - 1; b <= j + 1; b++)
						{
							if (cases_[a][b]->getTerrain() == Terrain::herbeux  && rand() % 100 >= 0 && a % 2 == 0 && b % 2 == 0)
							{
								nbEssaisArbre = 0;

								cases_[a][b]->setObstacle(Obstacle::arbre);
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
						if (tour && cases_[tabBaseArbreForet[i].x + 2][tabBaseArbreForet[i].y]->getTerrain() == Terrain::herbeux)
						{
							cases_[tabBaseArbreForet[i].x + 2][tabBaseArbreForet[i].y]->setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].x = tabBaseArbreForet[i].x + 2;
							tour = false;
						}
						else if (cases_[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y + 2]->getTerrain() == Terrain::herbeux)
						{
							cases_[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y + 2]->setObstacle(Obstacle::arbre);
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
						if (tour && cases_[tabBaseArbreForet[i].x - 2][tabBaseArbreForet[i].y]->getTerrain() == Terrain::herbeux)
						{
							cases_[tabBaseArbreForet[i].x - 2][tabBaseArbreForet[i].y]->setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].x = tabBaseArbreForet[i].x - 2;
							tour = false;
						}
						else if (cases_[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y + 2]->getTerrain() == Terrain::herbeux)
						{
							cases_[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y + 2]->setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].y = tabBaseArbreForet[i].y + 2;
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
						if (tour && cases_[tabBaseArbreForet[i].x + 2][tabBaseArbreForet[i].y]->getTerrain() == Terrain::herbeux)
						{
							cases_[tabBaseArbreForet[i].x + 2][tabBaseArbreForet[i].y]->setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].x = tabBaseArbreForet[i].x + 2;
							tour = false;
						}
						else  if (cases_[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y - 2]->getTerrain() == Terrain::herbeux)
						{
							cases_[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y - 2]->setObstacle(Obstacle::arbre);
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
						if (tour && cases_[tabBaseArbreForet[i].x - 2][tabBaseArbreForet[i].y]->getTerrain() == Terrain::herbeux)
						{
							cases_[tabBaseArbreForet[i].x - 2][tabBaseArbreForet[i].y]->setObstacle(Obstacle::arbre);
							tabBaseArbreForet[i].x = tabBaseArbreForet[i].x - 2;
							tour = false;
						}
						else  if (cases_[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y - 2]->getTerrain() == Terrain::herbeux)
						{
							cases_[tabBaseArbreForet[i].x][tabBaseArbreForet[i].y - 2]->setObstacle(Obstacle::arbre);
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
				if (cases_[i][j]->getTerrain() == Terrain::rocheux && cases_[i][j]->getObstacle() == Obstacle::aucun)
				{
					for (int a = i - 1; a <= i + 1; a++)
					{
						if (!(a < 32 && a >= 0))
							continue;
						for (int b = j - 1; b <= j + 1; b++)
						{
							if (!(b < 32 && b >= 0))
								continue;
							if (cases_[a][b]->getTerrain() == Terrain::herbeux)
							{
								cases_[a][b]->setObstacle(Obstacle::aucun);
							}
						}
					}
				}
			}
		}
	}

	void Grille::genererAutreAsset(int nbTotal)
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
				cases_[randI][randJ]->setObstacle(Obstacle::buisson);
				break;
			case 1:
				if (cases_[randI][randJ]->getTerrain() != Terrain::rocheux)
				{
					cases_[randI][randJ]->setObstacle(Obstacle::rocher);
				}
				break;
			}

		}
	}
}

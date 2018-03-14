#pragma once
#include "Case.h"
#include "Outils/Vecteur2.h"
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <forward_list>
#include <list>
#include "Unite/Archer.h"
#include "Unite/Tank.h"
#include "Unite/Soldat.h"

namespace Modele {

	class Grille {

	public :
		
		Grille(const Vecteur2<int>& dimension);
		virtual ~Grille();

		Vecteur2<int> getDimension() { return dimension_; }

		Case* getCase(const Vecteur2<int>& coordonees);
		Case* getCase(const int x, const int y);
		std::vector<std::vector<Case*>> getCases() { return cases_; }
		
		Unite* getUnite(const std::string& nom);
		std::set<Unite*> getUnites() { return unites_; }
		void ajouterUnite(Unite* unite);
		void supprimerUnite(Unite* unite);

		Unite* getUniteActuel();
		void finDeTour() { if(!ordreDeJeu_.empty())ordreDeJeu_.pop(); }
		void relancerOrdreDeJeu();

		std::forward_list<Vecteur2<int>> getCoordonneesCasesAdjacentes(const Vecteur2<int>& coordonnees);
		std::list<Vecteur2<int>> chercherCasesAccessiblesDeplacement(const Vecteur2<int>& depart, const int rayon);
		std::list<Vecteur2<int>> chercherCasesAccessiblesAttaque(const Vecteur2<int>& depart, const int rayon);
		std::stack<Vecteur2<int>> chercherChemin(const Vecteur2<int>& cible);
		std::list<Vecteur2<int>> getDerniereRechercheDeplacement() { return derniereRechercheDeplacement_; }
		std::list<Vecteur2<int>> getDerniereRechercheAttaque() { return derniereRechercheAttaque_; }
		void nettoyerDerniereRechercheDeplacement();
		void nettoyerDerniereRechercheAttaque();

		Unite * getProprietaireDerniereRechercheDeplacement() { return proprietaireDerniereRechercheDeplacement_; }
		Unite * getProprietaireDerniereRechercheAttaque() { return proprietaireDerniereRechercheAttaque_; }

		void deplacerUnite(const std::string& nom, const Vecteur2<int>& destination);
		void deplacerUnite(Unite* unite, const Vecteur2<int>& deplacement);

		//Generation procedurale	
		void genererEau(const int tailleMax);
		void genererPlage(const int circonferenceMax);
		void genererRocheux(const int tailleMax, const int epaisseur);
		void genererObstaclesRocheux();
		void genererAutreAsset( int nbTotal);
		void genererArbre( int intensite);

	private :

		Vecteur2<int> dimension_;

		std::vector<std::vector<Case*>> cases_;
		std::set<Unite*> unites_;
		std::priority_queue<Unite*> ordreDeJeu_;

		//Sauvegarde Recherche de chemin
		std::list<Vecteur2<int>> derniereRechercheDeplacement_;
		Unite * proprietaireDerniereRechercheDeplacement_;

		std::list<Vecteur2<int>> derniereRechercheAttaque_;
		Unite * proprietaireDerniereRechercheAttaque_;

		//Generation Procedurale
		std::vector<Vecteur2<int>> casesAquatiques_;
		std::vector<Vecteur2<int>> casesRocheuses_;
		std::vector<Vecteur2<int>> tabBaseArbreForet;

	};

}

#pragma once
#include "Case.h"
#include "Outils/Vecteur2.h"
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include "../../../../../../../Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.12.25827/include/forward_list"
#include <forward_list>

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

		Unite* getUniteActuel() { return ordreDeJeu_.empty() ? ordreDeJeu_.top() : nullptr; }
		void relancerOrdreDeJeu();

		std::forward_list<Vecteur2<int>> getCoordonneesCasesAdjacentes(const Vecteur2<int>& coordonnees);
		std::set<Vecteur2<int>> chercherCaseAccessible(const Vecteur2<int>& depart, const int rayon);
		std::stack<Vecteur2<int>> chercherChemin(const Vecteur2<int>& cible);
		std::set<Vecteur2<int>> getDerniereRecherche() { return derniereRecherche_; }
		void nettoyerDerniereRecherche() { derniereRecherche_.clear(); }

		Unite * getProprietaireDerniereRecherche() { return proprietaireDerniereRecherche_; }

		void deplacerUnite(const std::string& nom, const Vecteur2<int>& destination);
		void deplacerUnite(Unite* unite, const Vecteur2<int>& destination);

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
		std::set<Vecteur2<int>> derniereRecherche_;
		Unite * proprietaireDerniereRecherche_;

		//Generation Procedurale
		std::vector<Vecteur2<int>> casesAquatiques_;
		std::vector<Vecteur2<int>> casesRocheuses_;
		std::vector<Vecteur2<int>> tabBaseArbreForet;

	};

}

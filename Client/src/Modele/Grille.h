#pragma once
#include "Case.h"
#include "Outils/Vecteur2.h"
#include <vector>

namespace Modele {

	class Grille {

	public :
		
		Grille();

		void genererEau(int tailleMax);

		void genererPlage(int circonferenceMax);

		void genererRocheux(int tailleMax, int epaisseur);

		void genererObstaclesRocheux();

		void genererArbre( int intensite);
		
		void genererAutreAsset( int nbTotal); // generer les buissons ou autres frioritures

		Case getCase(int x, int y);
		
		void setUnite(Unite* unite, int x, int y);
		bool déplacerUnite(int x, int y, int a, int b); //renvoie true si le déplacement est réussi, deux ccordonnées départ ( x, y ) et deux coordonnées arrivée ( a, b ) 

	private :

		Case carte[32][32];
		std::vector<Vecteur2<int>> listeUnite;

		std::vector<Vecteur2<int>> tabAquatique;
		std::vector<Vecteur2<int>> tabRocheux;
		std::vector<Vecteur2<int>> tabBaseArbreForet;

	};

}
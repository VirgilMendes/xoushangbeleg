#pragma once
#include <iostream>
#include <string>
#include "Unite.h"
#include "Outils/enum.h"

namespace Modele
{
	BETTER_ENUM( Terrain, int, 
		herbeux,
		sableux,
		aquatique,
		rocheux
	)

	BETTER_ENUM( Obstacle, int,
		aucun,
		arbre,
		buisson,
		rocher
	)

	class Case
	{
	public :

		Case(const Vecteur2<int>& position);
		Case(const Vecteur2<int>& position, const Terrain& terrain, const Obstacle& obstacle);

		Terrain getTerrain() { return terrain_; }
		void setTerrain(const Terrain& terrain) { terrain_ = terrain; }

		Obstacle getObstacle() { return obstacle_; }
		void setObstacle(const Obstacle& obstacle) { obstacle_ = obstacle; }

		Unite* getUnite() { return unite_; }
		void setUnite(Unite* unite) { unite_ = unite; }

		Vecteur2<int > getPosition() { return position_; }
		void setPosition(const Vecteur2<int>& position) { position_ = position; }

		int getCout() { return cout_; }
		void setCout(int cout) { cout_ = cout; }

		Case * getCaseParent() { return caseParent_; }
		void setCaseParent(Case* caseParent) { caseParent_ = caseParent; }

	private :

		Vecteur2<int> position_;

		Terrain terrain_;
		Obstacle obstacle_;
		
		Unite* unite_;

		int cout_ = INT32_MAX;
		Case* caseParent_;
	};

}

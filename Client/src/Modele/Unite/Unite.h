#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "../Outils/Vecteur2.h"
#include "../Outils/enum.h"

namespace Modele
{

	BETTER_ENUM(Equipe, int,
		Rouge,
		Bleu
	)

	BETTER_ENUM(Classe, int,
		Archer,
		Tank,
		Soldat
	)

	class Unite
	{
	public:
		Unite(const std::string& nom, const Equipe& equipe, const Classe& classe, const int vieMax, const int attaque,
			const int defense,  const int porteeDeplacement, const int porteeAttaque, const Vecteur2<int>& position);
			
		std::string getNom() { return nom_; }
		void setEquipe(Equipe equipe);
		Equipe getEquipe() { return equipe_; }
		Classe getClasse() { return classe_; }
		
		void setVieMax(int vie) { vieMax_ = vie; }
		int getVieMax() { return vieMax_; }
		void prendreDommage(int vie) { vieCourante_ -= vie; }
		void prendreSoin(int soin) { vieCourante_ += soin; }
		int getVieCourante() { return vieCourante_; }

		void setDefense(const int defense) { defense_ = defense; }
		int getDefense() { return defense_; }
		void setAttaque(const int attaque) { attaque_ = attaque; }
		int getAttaque() { return attaque_; }
		void setPorteeDeplacement(const int portee) { porteeDeplacement_ = portee; }
		int getPorteeDeplacement() { return porteeDeplacement_; }
		void setPorteeAttaque(const int portee) { porteeAttaque_ = portee; }
		int getPorteeAttaque() { return porteeAttaque_; }

		void attaquer(Unite* unitee);

		void deplacer(Vecteur2<int> deplacement) { position_ += deplacement; }
		void setPosition(Vecteur2<int> position) { position_ = position; }
		Vecteur2<int> getPosition() { return position_; }

	private:

		std::string nom_;
		Equipe equipe_;
		Classe  classe_;

		int vieMax_;
		int vieCourante_;
		int attaque_;
		int defense_;
		int porteeDeplacement_;
		int porteeAttaque_;

		Vecteur2<int> position_;
	};
}

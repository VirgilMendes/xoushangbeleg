#pragma once
#ifndef DEF_UNITE
#define DEF_UNITE

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "Vecteur2.h"

namespace Modele
{

	enum class Equipe
	{
		Rouge,
		Bleu
	};

	class Unite
	{
	public:
		Unite(Equipe equipe, std::string nom, int vieM, int vieC, int statD, int statA, Vecteur2<int> pos);

		void setEquipe(Equipe BoR);
		Equipe getEquipe();

		void setNom(std::string nom);
		std::string getNom();

		void setVieMax(int vie);
		void setVieCourante(int vie);

		int getVieMax();
		int getVieCourante();

		void setStatDef(int stat);
		void setStatAtt(int stat);

		int getStatDef();
		int getStatAtt();

		void setPosition(Vecteur2<int> pos);

		Vecteur2<int> getPosition();

	private:
		Equipe equipe;
		std::string classe;
		std::string nom;

		int vieMax;
		int vieCourante;

		int statDef;
		int statAtt;

		Vecteur2<int> position;
	};
}
#endif

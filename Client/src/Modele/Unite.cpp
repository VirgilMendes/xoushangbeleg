#include "Unite.h"

namespace Modele
{

	Unite::Unite(Equipe equipe, std::string nom, int vieM, int vieC, int statD, int statA, Vecteur2<int> pos)
	{
		this->nom = nom;
		this->equipe = equipe;
		vieMax = vieM;
		vieCourante = vieC;
		statDef = statD;
		statAtt = statA;
		position = pos;


		if (vieCourante > vieMax)
		{
			vieCourante = vieMax;
		}
		if (vieCourante < 0)
		{
			vieCourante = 0;
		}


		if (statDef < 0)
		{
			statDef = 0;
		}
		if (statAtt < 0)
		{
			statAtt = 0;
		}
	}

	void Unite::setEquipe(Equipe BoR)
	{
		equipe = BoR;
	}

	Equipe Unite::getEquipe()
	{
		return equipe;
	}

	void Unite::setNom(std::string nom)
	{
		this->nom = nom;
	}

	std::string Unite::getNom()
	{
		return nom;
	}

	void Unite::setVieMax(int vie)
	{
		vieMax = vie;
		if (vieMax < vieCourante)
		{
			vieCourante = vieMax;
		}
	}
	void Unite::setVieCourante(int vie)
	{
		if (vie > vieMax)
		{
			vieCourante = vieMax;
		}
		else if (vie < vieMax && vie > 0)
		{
			vieCourante = vie;
		}
		else
		{
			vieCourante = 0;
		}
	}

	int Unite::getVieMax()
	{
		return vieMax;
	}
	int Unite::getVieCourante()
	{
		return vieCourante;
	}

	void Unite::setStatDef(int stat)
	{
		statDef = stat;
		if (statDef < 0)
		{
			statDef = 0;
		}
	}
	void Unite::setStatAtt(int stat)
	{
		statAtt = stat;
		if (statAtt < 0)
		{
			statAtt = 0;
		}
	}

	int Unite::getStatDef()
	{
		return statDef;
	}
	int Unite::getStatAtt()
	{
		return statAtt;
	}

	void Unite::setPosition(Vecteur2<int> pos)
	{
		position = pos;
	}
	Vecteur2<int> Unite::getPosition()
	{
		return position;
	}

}
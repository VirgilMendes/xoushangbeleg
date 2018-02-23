#include "Unite.h"
#include <pugixml.hpp>
#include <sstream>

namespace Modele
{

	Unite::Unite(Equipe equipe, Classe classe, std::string nom, int vieM, int vieC, int statD, int statA, Vecteur2<int> pos)
	{
		this->nom = nom;
		this->equipe = equipe;
		this->classe = classe;
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

	Classe Unite::getClasse()
	{
		return classe;
	}

	void Unite::setClasse(Classe classe)
	{
		this->classe = classe;
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
		pugi::xml_document doc;
		auto root = doc.append_child("paquet");
		pugi::xml_node nodeDeplacement = root.append_child("deplacement");
		pugi::xml_node nodeUnite = nodeDeplacement.append_child("unite");
		pugi::xml_node nodeNom = nodeUnite.append_child("nom");
		nodeNom.text().set(this->getNom().c_str());
		pugi::xml_node nodePosition = nodeDeplacement.append_child("position");
		pugi::xml_node nodeX = nodePosition.append_child("x");
		nodeX.text().set((std::to_string(pos.x).c_str()));
		pugi::xml_node nodeY = nodePosition.append_child("y");
		nodeY.text().set(std::to_string(pos.y).c_str());
		std::stringstream flux;
		doc.print(flux);
		std::cout << flux.str() << std::endl;
		
	}
	Vecteur2<int> Unite::getPosition()
	{
		return position;
	}

}
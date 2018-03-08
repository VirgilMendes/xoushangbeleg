#include "Unite.h"
#include <pugixml.hpp>
#include <sstream>

namespace Modele
{
	Unite::Unite(const std::string& nom, const Equipe& equipe, const Classe& classe, const int vieMax, const int attaque, 
		const int defense, const int porteeAttaque, const int porteeDeplacement, const Vecteur2<int>& position):
	nom_(nom), equipe_(equipe), classe_(classe), vieMax_(vieMax), vieCourante_(vieMax_), attaque_(attaque), defense_(defense),
	porteeAttaque_(porteeAttaque), porteeDeplacement_(porteeDeplacement), position_(position)
	{
	}

	void Unite::attaquer(Unite* unitee)
	{

	}
}

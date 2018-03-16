#include "Unite.h"
#include <pugixml.hpp>
#include <sstream>

namespace Modele
{
	Unite::Unite(const std::string& nom, const Equipe& equipe, const Classe& classe, const int vieMax, const int attaque, 
		const int defense,  const int porteeDeplacement, const int porteeAttaque, const Vecteur2<int>& position):
	nom_(nom), equipe_(equipe), classe_(classe), vieMax_(vieMax), vieCourante_(vieMax_), attaque_(attaque), defense_(defense),
	porteeDeplacement_(porteeDeplacement), porteeAttaque_(porteeAttaque), position_(position)
	{
	}

	void Unite::attaquer(Unite* unitee)
	{
		unitee->prendreDommage(attaque_);
	}
}

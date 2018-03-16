#pragma once
#include "Unite.h"
#include <iostream>
#include <string>

namespace Modele
{

	class Tank : public Unite
	{
	public :
		Tank(std::string nom, Equipe equipe, Vecteur2<int> position);

	};

}
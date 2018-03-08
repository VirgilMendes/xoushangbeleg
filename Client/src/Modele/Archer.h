#pragma once
#include "Unite.h"
#include <iostream>
#include <string>

namespace Modele
{

	class Archer : public Unite
	{
	public:
		Archer(std::string nom, Equipe equipe, Vecteur2<int> position);

	};

}
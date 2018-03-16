#pragma once
#include "Unite.h"
#include <iostream>
#include <string>

namespace Modele
{

	class Soldat : public Unite
	{
	public:
		Soldat(std::string nom, Equipe equipe, Vecteur2<int> position);

	};

}
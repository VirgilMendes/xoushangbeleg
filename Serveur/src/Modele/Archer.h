#pragma once
#include "Unite.h"
#include <iostream>
#include <string>

namespace Modele
{

	class Archer : public Unite
	{
	public:
		Archer(Equipe equ, std::string surnomAmusant, int x, int y);

	};

}
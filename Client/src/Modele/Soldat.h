#pragma once
#include "Unite.h"
#include <iostream>
#include <string>

namespace Modele
{

	class Soldat : public Unite
	{
	public:
		Soldat(Equipe equ, std::string surnomAmusant,int x, int y);

	};

}
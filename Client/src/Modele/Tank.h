#pragma once
#include "Unite.h"
#include <iostream>
#include <string>

namespace Modele
{

	class Tank : public Unite
	{
	public :
		Tank( Equipe equipe,std::string surnomAmusant, int x, int y);

	};

}
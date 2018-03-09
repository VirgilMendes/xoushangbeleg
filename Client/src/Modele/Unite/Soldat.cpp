#include "Soldat.h"
#include <SFML/Graphics.hpp>

namespace Modele
{
	Soldat::Soldat(std::string nom, Equipe equipe, Vecteur2<int> position) : Unite(nom, equipe, Classe::Soldat, 110, 75, 100, 4, 1, position)
	{}
}
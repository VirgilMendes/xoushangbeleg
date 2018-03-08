#include "Archer.h"
#include <SFML/Graphics.hpp>

namespace Modele
{
	Archer::Archer(std::string nom, Equipe equipe, Vecteur2<int> position) : Unite(nom, equipe, Classe::Archer, 75, 50, 50, 3, 5 , position)
	{}
}
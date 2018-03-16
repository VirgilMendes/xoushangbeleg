#include "Tank.h"
#include <SFML/Graphics.hpp>

namespace Modele
{
	Tank::Tank(std::string nom, Equipe equipe, Vecteur2<int> position) : Unite(nom, equipe, Classe::Tank, 150, 100, 80, 2, 1, position)
	{}
}
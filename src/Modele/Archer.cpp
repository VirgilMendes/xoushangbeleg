#include "Archer.h"
#include <SFML/Graphics.hpp>

namespace Modele
{
	Archer::Archer(Equipe equ, std::string nom, int x, int y) : Unite(equ, nom, 75, 75, 50, 50, Vecteur2<int>(x, y))
	{}
}
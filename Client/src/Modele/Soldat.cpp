#include "Soldat.h"
#include <SFML/Graphics.hpp>

namespace Modele
{
	Soldat::Soldat(Equipe equ, std::string nom, int x, int y) : Unite(equ, Classe::Soldat,nom, 110, 110, 75, 100, Vecteur2<int>(x, y))
	{}
}
#include "Tank.h"
#include <SFML/Graphics.hpp>

namespace Modele
{
	Tank::Tank(Equipe equ,std::string nom, int x, int y): Unite(equ,nom, 150, 150, 100, 80, Vecteur2<int>(x,y))
	{}
}
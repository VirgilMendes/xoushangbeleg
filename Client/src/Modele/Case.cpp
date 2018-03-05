#include "Case.h"

namespace Modele
{
	Case::Case(const Vecteur2<int>& position) : position_(position), terrain_(Terrain::herbeux), obstacle_(Obstacle::aucun)
	{
	}

	Case::Case(const Vecteur2<int>& position, const Terrain& terrain, const Obstacle& obstacle) : position_( position), terrain_(terrain), obstacle_(obstacle)
	{
	}
}

#include "Case.h"

namespace Modele
{
	Case::Case(Unite* unite, Terrain terrain, Obstacle obstacle) : unite(unite), terrain(terrain), obstacle(obstacle)
	{}

	Unite* Case::getUnite()
	{
		return unite;
	}
	void Case::setUnite(Unite* unite)
	{
		this->unite = unite;
	}

	Obstacle Case::getObstacle()
	{
		return obstacle;
	}
	void Case::setObstacle(Obstacle obstacle)
	{
		this->obstacle = obstacle;
	}

	Terrain Case::getTerrain()
	{
		return terrain;
	}
	void Case::setTerrain(Terrain terrain)
	{
		this->terrain = terrain;
	}

}